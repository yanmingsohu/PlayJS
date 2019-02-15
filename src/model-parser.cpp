#include "js.h"
#include "vm.h"
#include "fs.h"
#include "model-ply.h"
#include "util.h"


typedef std::unique_ptr<char[]> BufferPtr;


static void freeBuf(void* data) {
    delete [] data;
}


static size_t __read(JsValueRef fileArg, BufferPtr& ptr) {
    char *buf;
    std::string &file = stringValue(fileArg);
    size_t rlen = readFile(file, &buf);
    if (rlen == 0) {
        pushException("Cannot read: "+ file);
        return 0;
    }
    ptr.reset(buf);
    return rlen;
}


JSS_FUNC(ply, args, ac) {
    JSS_CHK_ARG(1, ply(filename));
    BufferPtr filebuf;
    size_t rlen = __read(args[1], filebuf);
    if (rlen == 0) { return 0; }

    try {
        LocalVal ret = JVM->createObject();
        PlyParser ply(filebuf.get(), rlen);
        int buflen = 0;

        char* buf = ply.vertexBuf(buflen);
        if (buf) {
            JsValueRef val = 0;
            JsCreateExternalArrayBuffer(buf, buflen, freeBuf, buf, &val);
            ret.put("vertex", val);
        }

        buf = ply.indexBuf(buflen);
        if (buf) {
            JsValueRef val = 0;
            JsCreateExternalArrayBuffer(buf, buflen, freeBuf, buf, &val);
            ret.put("index", val);
        }
        return ret;
    } catch (std::runtime_error& e) {
        pushException(e.what());
        return 0;
    }
}


JSS_INIT_MODULE(installModelParser) {
    JSS_MOD(model_parser);
    JSS_BIND(ply);
}