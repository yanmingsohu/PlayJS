#include "threads.h"
#include "export-js.h"
#include "fs.h"
#include "util.h"

#include <map>
#include <mutex>

using std::map;
using std::thread;
using std::string;
using std::mutex;
using std::lock_guard;

typedef map<threadId, thread*> ThreadMap;

static int nextId = 100;
static mutex lock_map;
static ThreadMap tmap;


static void freeThread(threadId* _id) {
    lock_guard<mutex> guard(lock_map);
    threadId id = (threadId) _id;
    tmap.erase((threadId)id);
}


static string& operator+(string& s, int i) {
    return s.append(std::to_string(i));
}


void loadScript(string& filename, threadId id) {
    LocalResource<threadId> freeThreadHandle((threadId*)id, freeThread);
    println("Start Script '"+ filename +"' on thread [id:"+ id +"]");

    std::string code;
    if (FAILED == readTxtFile(filename, code)) {
        println("Read '"+ filename +"' error");
        return;
    }

    VM vm;
    installConsole(&vm);
    installFileSystem(&vm);
    installUtf(&vm);
    installThread(&vm);

    JsErrorCode r = vm.loadModule(0, filename, code);
    if (r) {
        println("Load Module '"+ filename +"' failed code: "+ r);
    }

    LocalVal err = vm.checkError();
    if (err.notNull()) {
        LocalVal st = err.get("stack");
        if (st.notNull()) {
            println("Exit on failed: "+ st.toString());
        }
        else {
            println("Exit on failed: "+ err.toString());
        }
    }
    println("Script '"+ filename+ "' on Thread [id:"+ int(id) +"] Exit");
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

    for (auto it = tmap.begin(); it != tmap.end(); ++it) {
        println(std::string("Wait thread [id:")+ (it->first) +"]");
        it->second->join();
    }
}


static JsValueRef js_run(JsValueRef callee, JsValueRef *args, unsigned short ac,
                         JsNativeFunctionInfo *info, void *level) 
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
                           JsNativeFunctionInfo *info, void *level)
{
    if (ac != 2) {
        pushException("bad arguments, sleep(ms)");
        return 0;
    }
    int time = intValue(args[1]);
    if (time > 0) {
        std::chrono::duration<int, std::milli> t(time);
        std::this_thread::sleep_for(t);
    }
    return 0;
}


void installThread(VM* vm) {
    LocalVal thread = vm->createObject();
    vm->getGlobal().put("thread", thread);
    thread.put("run",   vm->createFunction(&js_run,   "run"));
    thread.put("sleep", vm->createFunction(&js_sleep, "sleep"));
}