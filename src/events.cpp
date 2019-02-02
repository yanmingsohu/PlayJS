#include "vm.h"
#include "threads.h"

#include <map>
#include <set>
#include <string>
#include <forward_list>
#include <mutex>
#include <shared_mutex>

using std::map;
using std::set;
using std::string;
using std::forward_list;
using std::mutex;
using std::lock_guard;
using std::shared_mutex;

class InnerEvent;

typedef std::pair<threadId, InnerEvent*> EventOnThread;

static map<threadId, InnerEvent*> all_thread;
static shared_mutex allEventLocker;


class EventData {
public:
    string name;
    LocalVal value;

    EventData(string& _name, LocalVal _value)
    : name(_name), value(_value) {}
};


class InnerEvent {
private:
    bool running;
    VM *vm;
    //
    // 在当前线程上注册的监听器
    //
    map<string, set<LocalVal>> listener;
    //
    // 等待发送到全局的消息队列
    //
    forward_list<EventData> send;
    //
    // 从全局接受的消息, 等待监听器处理
    //
    forward_list<EventData> recv;


    void recvIfHasListener(EventData d) {
        if (listener.count(d.name) > 0) {
            recv.push_front(d);
        }
    }

    bool dispatchError(JsValueRef err) {
        auto err_it = listener.find("error");
        if (err_it == listener.end()) {
            JsSetException(err);
            return false;
        }
        for (auto func_it = err_it->second.begin();
            func_it != err_it->second.end(); ++func_it)
        {
            func_it->call(err);
        }
        return true;
    }

public:
    InnerEvent(VM *_vm) : vm(_vm), running(true) {
    }


    void on(string& name, LocalVal func) {
        auto it = listener.find(name);
        if (it == listener.end()) {
            listener[name].insert(func);
        }
        else {
            it->second.insert(func);
        }
    }


    int off(string& name) {
        int removed = 0;
        auto it = listener.find(name);
        if (it != listener.end()) {
            removed = it->second.size();
            it->second.clear();
        }
        return removed;
    }


    int off(string& name, LocalVal func) {
        int removed = 0;
        auto it = listener.find(name);
        if (it != listener.end()) {
            removed = it->second.erase(func);
        }
        return removed;
    }


    void emit(string& name, LocalVal data) {
        send.push_front(EventData(name, data));
    }


    bool getMessage() {
        //TODO: 等待新的消息到达
        while (!recv.empty()) {
            auto data = recv.front();
            recv.pop_front();
            auto lset_it = listener.find(data.name);

            if (lset_it == listener.end()) 
                continue;

            for (auto lit = lset_it->second.begin(); 
                lit != lset_it->second.end(); ++lit)
            {
                lit->call(data.value);
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
        if (send.empty()) return;

        std::shared_lock<shared_mutex> _lock(allEventLocker);
        for (auto it_thread = all_thread.begin(); 
            it_thread != all_thread.end(); ++it_thread)
        {
            for (auto it_data = send.begin(); 
                it_data != send.end(); ++it_data)
            {
                it_thread->second->recvIfHasListener(*it_data);
            }
            //TODO: 线程上发送: 新的消息已经到达
        }
        send.clear();
    }
};


static JsValueRef js_on(JsValueRef callee, JsValueRef *args, unsigned short ac,
                        JsNativeFunctionInfo *info, void *_ie) 
{
    InnerEvent* ie = (InnerEvent*) _ie;
    return 0;
}


void installEvents(VM* vm) {
    InnerEvent *ie = new InnerEvent(vm);
    threadId tid = vm->thread();
    std::unique_lock<shared_mutex> _lock(allEventLocker);
    all_thread.insert(EventOnThread(tid, ie));

    LocalVal events = vm->createObject();
    vm->getGlobal().put("events", events);

    events.put("on", vm->createFunction(&js_on, "info", ie));
}


void destoryEvents(VM* vm) {
    threadId tid = vm->thread();
    std::unique_lock<shared_mutex> _lock(allEventLocker);
    all_thread.erase(tid);
}