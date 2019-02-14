#include "threads.h"
#include "export-js.h"
#include "fs.h"
#include "util.h"
#include "vm.h"

#include <map>
#include <mutex>

using std::map;
using std::thread;
using std::string;
using std::mutex;
using std::lock_guard;

typedef map<threadId, thread*> ThreadMap;

static volatile int nextId = 0x10;
static mutex lock_map;
static ThreadMap tmap;


static void freeThread(threadId* _id) {
    lock_guard<mutex> guard(lock_map);
    threadId id = reinterpret_cast<threadId>(_id);
    tmap.erase((threadId)id);
}


static string& operator+(string& s, int i) {
    return s.append(std::to_string(i));
}


static void installJsLibrary(VM* vm) {
    installConsole(vm);
    installFileSystem(vm);
    installUtf(vm);
    installThread(vm);
    installEvents(vm);
    installShared(vm);
    installGL(vm);
    installImage(vm);
}


static void unstallJsLIbrary(VM* vm) {
    destoryEvents(vm);
    unstallGL(vm);
}


void loadScript(string& filename, threadId id) {
    LocalResource<threadId> freeThreadHandle(reinterpret_cast<threadId*>(id), freeThread);
    println("Start Script '"+ filename +"'", id);

    std::string code;
    if (FAILED == readTxtFile(filename, code)) {
        println("Read '"+ filename +"' error", id);
        return;
    }

    VM vm(id);
    installJsLibrary(&vm);

    JsErrorCode r = vm.loadModule(0, filename, code);
    if (r) {
        println("Load Module '"+ filename +"' failed code: "+ r, id);
    }

    LocalVal err = vm.checkError();
    if (err.notNull()) {
        LocalVal st = err.get("stack");
        if (st.notNull()) {
            println("Exit on failed: "+ st.toString(), id);
        }
        else {
            println("Exit on failed: "+ err.toString(), id);
        }
    }
    unstallJsLIbrary(&vm);
    println("Script '"+ filename+ "' Exit", id);
}


threadId loadScriptInNewThread(string& fileName) {
    lock_guard<mutex> guard(lock_map);
    threadId id = nextId++;
    thread* newThread = new thread(loadScript, fileName, id);
    tmap.insert(ThreadMap::value_type(id, newThread));
    return id;
}


thread* getThread(threadId i) {
    lock_guard<mutex> guard(lock_map);
    auto p = tmap.find(i);
    if (p == tmap.end()) {
        return 0;
    }
    return p->second;
}


void joinAll() {
    println(string("Running Thread: ")+ tmap.size());
    lock_map.lock();

    for (auto it = tmap.begin(); it != tmap.end(); ++it) {
        //
        // 当线程运行时可能会启动新的线程, 交叉锁可以防止死锁.
        //
        lock_map.unlock();
        println(std::string("Wait thread [id:")+ (it->first) +"]");
        it->second->join();
        lock_map.lock();
    }
    lock_map.unlock();
}


static JsValueRef js_run(JsValueRef callee, JsValueRef *args, unsigned short ac,
                         JsNativeFunctionInfo *info, void *d) 
{
    if (ac != 2) {
        pushException("bad arguments, run(scriptFilePath)");
        return 0;
    }
    LocalVal filenameArg(args[1]);
    string filename = filenameArg.toString();
    threadId id = loadScriptInNewThread(filename);
    return wrapJs(id);
}


static JsValueRef js_sleep(JsValueRef callee, JsValueRef *args, unsigned short ac,
                           JsNativeFunctionInfo *info, void *d)
{
    if (ac != 2) {
        pushException("bad arguments, sleep(ms)");
        return 0;
    }
    int time = intValue(args[1]);
    if (time > 0) {
        std::this_thread::sleep_for(
            std::chrono::duration<int, std::milli>(time));
    }
    return 0;
}


static JsValueRef js_running(JsValueRef callee, JsValueRef *args, unsigned short ac,
                             JsNativeFunctionInfo *info, void *d)
{
    if (ac != 2) {
        pushException("bad arguments, get(threadid)");
        return 0;
    }
    int id = intValue(args[1]);
    return wrapJs(0 != getThread(id));
}


static JsValueRef js_id(JsValueRef callee, JsValueRef *args, unsigned short ac,
    JsNativeFunctionInfo *info, void *id)
{
    return wrapJs(reinterpret_cast<threadId>(id));
}


void installThread(VM* vm) {
    LocalVal thread = vm->createObject();
    vm->getGlobal().put("thread", thread);
    void * id = reinterpret_cast<void*>(vm->thread());

    DEF_JS_FUNC(vm, id, thread, id,      js_id);
    DEF_JS_FUNC(vm, 0,  thread, run,     js_run);
    DEF_JS_FUNC(vm, 0,  thread, sleep,   js_sleep);
    DEF_JS_FUNC(vm, 0,  thread, wait,    js_sleep);
    DEF_JS_FUNC(vm, 0,  thread, running, js_running);
}