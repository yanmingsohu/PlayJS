#include "fs.h"
#include "vm.h"


#define GET_FD_FROM_JS(_name_, _js_obj_) \
    FILE* _name_ = 0; \
    if (JsGetExternalData(_js_obj_, (void**)&_name_)) { \
        pushException("is not file handle"); \
        return 0; \
    }


int readFile(std::string file, char **buf) {
    FILE* fd = 0;
    if (fopen_s(&fd, file.c_str(), "rb")) {
        return FAILED;
    }
    fseek(fd, 0, SEEK_END);
    int len = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    *buf = new char[len];
    int rlen = fread(*buf, sizeof(char), len, fd);
    fclose(fd);
    return rlen;
}


int readTxtFile(std::string fileName, std::string &content) {
    char *buf = 0;
    int len = readFile(fileName, &buf);
    if (len > 0) {
        content.append(buf, len);
    }
    delete[] buf;
    return len;
}


static void finalFile(void * data) {
    FILE* fd = (FILE*) data;
    if (fd) {
        fclose(fd);
    }
}


static JsValueRef js_open(JsValueRef callee, JsValueRef *args, unsigned short ac,
                          JsNativeFunctionInfo *info, void *d)
{
    if (ac != 3) {
        pushException("bad arguments length, open(path, mode)");
        return 0;
    }
    LocalVal path(args[1]);
    LocalVal flag(args[2]);

    FILE* fd = 0;
    if (fopen_s(&fd, path.toString().c_str(), flag.toString().c_str())) {
        pushException("open file fail "+ path.toString());
        return 0;
    }
    JsValueRef handle = 0;
    JsCreateExternalObject(fd, &finalFile, &handle);
    return handle;
}


static JsValueRef js_close(JsValueRef callee, JsValueRef *args, unsigned short ac,
                           JsNativeFunctionInfo *info, void *d) 
{
    if (ac != 2) {
        pushException("bad arguments length, close(fd)");
        return 0;
    }
    GET_FD_FROM_JS(fd, args[1]);
    fclose(fd);
    return 0;
}


static JsValueRef js_read(JsValueRef callee, JsValueRef *args, unsigned short ac,
                          JsNativeFunctionInfo *info, void *d) 
{
    if (ac != 6) {
        pushException("bad arguments, read(fd, buffer, b_offset, b_length, pos)");
        return 0;
    }
    GET_FD_FROM_JS(fd, args[1]);
    LocalArray arr(args[2]);
    int b_offset = intValue(args[3]);
    int b_length = intValue(args[4]);
    int pos = intValue(args[5]);
    int rlen = fread(arr.buffer(), 1, arr.length(), fd);
    return wrapJs(rlen);
}


void installFileSystem(VM *vm) {
    LocalVal fs = vm->createObject();
    vm->getGlobal().put("fs", fs);

    LocalVal open = vm->createFunction(&js_open, "open");
    fs.put("open", open);
    fs.put("openSync", open);

    LocalVal close = vm->createFunction(&js_close, "close");
    fs.put("close", close);
    fs.put("closeSync", close);

    LocalVal read = vm->createFunction(&js_read, "read");
    fs.put("read", read);
    fs.put("readSync", read);
}