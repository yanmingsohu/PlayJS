#include "vm.h"
#include "threads.h"
#include "shared.h"
#include "concurrentqueue/concurrentqueue.h"
#include "object_threadsafe/safe_ptr.h"

#include <map>
#include <set>
#include <string>
#include <forward_list>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <condition_variable>

using std::map;
using std::set;
using std::string;
using std::forward_list;
using std::mutex;
using std::lock_guard;
using std::shared_mutex;
using std::condition_variable;
using std::unique_lock;
using moodycamel::ConcurrentQueue;

class InnerEvent;

typedef std::pair<threadId, InnerEvent*> EventOnThread;
typedef LocalVal JSMessageCallback;

static const string EXIT_EVENT = "exit";
static map<threadId, InnerEvent*> all_thread;
static shared_mutex all_thread_locker;
static bool running = true;


class EventData {
public:
    string name;
    SharedValue value;

    EventData(string& _name, LocalVal _value, threadId tid)
    : name(_name), value(tid, _value) {}

    EventData() : name(""), value() {}

    //
    // 数据无效返回 true
    //
    bool fail() {
        return value.empty();
    }
};


class InnerEvent {
private:
    threadId tid;
    //
    // 在当前线程上注册的监听器
    //
    map<string, set<JSMessageCallback>> listener;
    sf::safe_ptr<map<string, int>> listener_count;
    //
    // 等待发送到全局的消息队列.
    // 访问 send 的过程始终在当前线程上, 不需要多线程保护.
    //
    forward_list<EventData> send;
    //
    // 从全局接受的消息, 等待监听器处理.
    //
    moodycamel::ConcurrentQueue<EventData> recv;

    mutex message_mx;
    condition_variable wait_new_message;


    void recvIfHasListener(EventData d) {
        if ((*listener_count)[d.name] > 0) {
            recv.enqueue(d);
        }
    }


    bool dispatchError(JsValueRef err) {
        bool hasErr = false;
        auto err_it = listener.find("error");

        if (err_it == listener.end()) {
            JsSetException(err);
            return false;
        }

        for (auto func_it = err_it->second.begin();
            func_it != err_it->second.end(); ++func_it)
        {
            //
            // 如果 error 处理器抛出异常则直接抛出 js 异常
            //
            func_it->call(err);
            JsHasException(&hasErr);
            if (hasErr) return false;
        }
        return true;
    }


    void newMessageReady() {
        wait_new_message.notify_one();
    }


    void waitNewMessage() {
        unique_lock<mutex> luck(message_mx);
        if (running && recv.size_approx() < 1) {
            wait_new_message.wait(luck);
        }
    }

public:
    InnerEvent(threadId _tid) : tid(_tid) {
    }


    void on(string& name, LocalVal func) {
        auto it = listener.find(name);
        if (it == listener.end()) {
            listener[name].insert(func);
            (*listener_count)[name] = 1;
        }
        else {
            it->second.insert(func);
            (*listener_count)[name] = listener.count(name);
        }
    }


    int off(string& name) {
        int removed = 0;
        auto it = listener.find(name);
        if (it != listener.end()) {
            removed = it->second.size();
            it->second.clear();
            (*listener_count)[name] = 0;
        }
        return removed;
    }


    int off(string& name, LocalVal func) {
        int removed = 0;
        auto it = listener.find(name);
        if (it != listener.end()) {
            removed = it->second.erase(func);
            (*listener_count)[name] = listener.count(name);
        }
        return removed;
    }


    bool emit(string& name, LocalVal data) {
        if (running && name == EXIT_EVENT) {
            running = false;
        }
        EventData ed(name, data, tid);
        if (! ed.fail()) {
            send.push_front(EventData(name, data, tid));
            return true;
        }
        return false;
    }


    bool getMessage() {
        waitNewMessage();

        EventData data;
        bool found;

        while (found = recv.try_dequeue(data)) {
            auto lset_it = listener.find(data.name);

            if (lset_it == listener.end()) 
                continue;

            auto funcs = lset_it->second;

            for (auto lit = funcs.begin(); lit != funcs.end(); ++lit) {
                lit->call(data.value.js());
                JsValueRef exception = checkError();
                if (exception) {
                    if (!dispatchError(exception)) {
                        return running;
                    }
                }
            }
        }
        return running;
    }

    //
    // 把消息推送到所有感兴趣的线程上
    //
    void dispatchMessage() {
        if (send.empty()) {
            return;
        }

        std::shared_lock<shared_mutex> _lock(all_thread_locker);
        for (auto it_thread = all_thread.begin(); 
            it_thread != all_thread.end(); ++it_thread)
        {
            //
            // 开始进入另一个线程的领域
            //
            for (auto it_data = send.begin(); 
                it_data != send.end(); ++it_data)
            {
                it_thread->second->recvIfHasListener(*it_data);
            }
            it_thread->second->newMessageReady();
        }
        send.clear();
    }
};


static JsValueRef js_on(JsValueRef callee, JsValueRef *args, unsigned short ac,
                        JsNativeFunctionInfo *info, void *_ie) 
{
    if (ac != 3) {
        pushException("bad arguments, on(message_name, callback)");
        return 0;
    }
    string name = toString(args[1]);
    LocalVal func(args[2]);
    if (!func.isFunction()) {
        pushException("callback not function");
        return 0;
    }

    InnerEvent* ie = (InnerEvent*) _ie;
    ie->on(name, func);
    return 0;
}


static JsValueRef js_off(JsValueRef callee, JsValueRef *args, unsigned short ac,
                         JsNativeFunctionInfo *info, void *_ie)
{
    if (ac != 3 && ac != 2) {
        pushException("bad arguments, off(message_name[, callback])");
        return 0;
    }

    InnerEvent* ie = (InnerEvent*)_ie;
    string name = toString(args[1]);
    int delete_count = 0;

    if (ac == 2) {
        delete_count = ie->off(name);
    }
    else {
        LocalVal func(args[2]);
        if (!func.isFunction()) {
            pushException("callback not function");
            return 0;
        }
        delete_count = ie->off(name, func);
    }

    return wrapJs(delete_count);
}


static JsValueRef js_emit(JsValueRef callee, JsValueRef *args, unsigned short ac,
                          JsNativeFunctionInfo *info, void *_ie)
{
    if (ac != 3) {
        pushException("bad arguments, emit(message_name, value)");
        return 0;
    }
    string name = toString(args[1]);
    InnerEvent* ie = (InnerEvent*)_ie;
    ie->emit(name, args[2]);
    return 0;
}


static JsValueRef js_getm(JsValueRef callee, JsValueRef *args, unsigned short ac,
                          JsNativeFunctionInfo *info, void *_ie) 
{
    InnerEvent* ie = (InnerEvent*)_ie;
    bool r = ie->getMessage();
    return wrapJs(r);
}


static JsValueRef js_dispatch(JsValueRef callee, JsValueRef *args, unsigned short ac,
                              JsNativeFunctionInfo *info, void *_ie)
{
    InnerEvent* ie = (InnerEvent*)_ie;
    ie->dispatchMessage();
    return 0;
}


void installEvents(VM* vm) {
    threadId tid = vm->thread();
    InnerEvent *ie = new InnerEvent(tid);
    std::unique_lock<shared_mutex> _lock(all_thread_locker);
    all_thread.insert(EventOnThread(tid, ie));

    LocalVal events = vm->createObject();
    vm->getGlobal().put("events", events);

    events.put("on",   vm->createFunction(&js_on,   "on",   ie));
    events.put("off",  vm->createFunction(&js_off,  "off",  ie));
    events.put("emit", vm->createFunction(&js_emit, "emit", ie));

    events.put("getMessage", 
        vm->createFunction(&js_getm, "getMessage", ie));
    events.put("dispatchMessage", 
        vm->createFunction(&js_dispatch, "dispatchMessage", ie));
}


void destoryEvents(VM* vm) {
    threadId tid = vm->thread();
    std::unique_lock<shared_mutex> _lock(all_thread_locker);

    auto it = all_thread.find(tid);
    if (it != all_thread.end()) {
        delete it->second;
        all_thread.erase(it);
    }
}