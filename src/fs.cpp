#include "fs.h"
#include "vm.h"
#include "util.h"

#include <filesystem>

namespace fs = std::experimental::filesystem::v1;


//
// TODO: 如果 external 中的指针不是 FILE 怎么办 ???
//
#define GET_FD_FROM_JS(_name_, _js_obj_) \
    FILE* _name_ = 0; \
    if (JsGetExternalData(_js_obj_, (void**)&_name_)) { \
        pushException("is not file handle"); \
        return 0; \
    }


int readFile(std::string& file, char **buf) {
    FILE* fd = 0;
    if (fopen_s(&fd, file.c_str(), "rb")) {
        return FAILED;
    }
    
    LocalResource<FILE, int> close(fd, fclose);
    fseek(fd, 0, SEEK_END);
    int len = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    *buf = new char[len];
    int rlen = fread(*buf, sizeof(char), len, fd);
    return rlen;
}


int readTxtFile(std::string& fileName, std::string &content) {
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
    if (ac != 6 && ac != 5) {
        pushException("bad arguments, read(fd, buffer, b_offset, b_length, f_pos)");
        return 0;
    }
    GET_FD_FROM_JS(fd, args[1]);
    LocalArray arr(args[2]);
    int b_offset = intValue(args[3], 0);
    int b_length = intValue(args[4], arr.length());

    b_offset = max(0, min(b_offset, arr.length()));
    b_length = max(0, min(arr.length() - b_offset, b_length));
    
    if (ac == 6 && isJsNumber(args[5])) {
        int pos = intValue(args[5]);
        fseek(fd, pos, SEEK_SET);
    }
    int rlen = fread(arr.buffer()+b_offset, 1, b_length, fd);
    return wrapJs(rlen);
}


static JsValueRef js_write(JsValueRef callee, JsValueRef *args, unsigned short ac,
                           JsNativeFunctionInfo *info, void *d)
{
    if (ac != 6 && ac != 5) {
        pushException("bad arguments, write(fd, buffer, b_offset, b_length, f_pos)");
        return 0;
    }
    GET_FD_FROM_JS(fd, args[1]);
    LocalArray arr(args[2]);
    int b_offset = intValue(args[3]);
    int b_length = intValue(args[4]);

    b_offset = max(0, min(b_offset, arr.length()));
    b_length = max(0, min(arr.length() - b_offset, b_length));

    if (ac == 6 && isJsNumber(args[5])) {
        int pos = intValue(args[5]);
        fseek(fd, pos, SEEK_SET);
    }
    int wlen = fwrite(arr.buffer()+b_offset, 1, b_length, fd);
    return wrapJs(wlen);
}


static JsValueRef js_file_size(JsValueRef callee, JsValueRef *args, unsigned short ac,
                               JsNativeFunctionInfo *info, void *d)
{
    if (ac != 2) {
        pushException("bad arguments, fileSize(filename)");
        return 0;
    }
    std::string filename = toString(args[1]);
    return wrapJs((int) fs::file_size(filename));
}


static JsValueRef js_fpos(JsValueRef callee, JsValueRef *args, unsigned short ac,
                          JsNativeFunctionInfo *info, void *d)
{
    if (ac != 2) {
        pushException("bad arguments, fpos(fd)");
        return 0;
    }
    GET_FD_FROM_JS(fd, args[1]);
    fpos_t pos = 0;
    if (fgetpos(fd, &pos)) {
        pushException("cannot get file pos: "+ errno);
        return 0;
    }
    return wrapJs((double)pos);
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

    LocalVal write = vm->createFunction(&js_write, "write");
    fs.put("write", write);
    fs.put("writeSync", write);

    LocalVal file_size = vm->createFunction(&js_file_size, "fileSize", vm);
    fs.put("fileSize", file_size);

    LocalVal fpos = vm->createFunction(&js_fpos, "fpos", vm);
    fs.put("fpos", fpos);
    fs.put("fposSync", fpos);
}