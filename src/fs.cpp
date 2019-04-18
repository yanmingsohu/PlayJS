#include "fs.h"
#include "vm.h"
#include "util.h"
#include "shared.h"

#include <filesystem>
#include <iostream>
#include <stdio.h>

namespace fs = std::experimental::filesystem::v1;

//
// 下载并编译依赖 https://icculus.org/physfs
// 在 `/deps/physfs/Release` 目录中
//
#ifdef WIN32
#pragma comment(lib, "physfs-static.lib")
#endif


#define GET_FD_FROM_JS(_name_, _js_obj_) \
    FILE* _name_ = 0; \
    int _handle = intValue(_js_obj_); \
    auto _s_ptr = get_shared_resource<FILE>(_handle); \
    if (!_s_ptr) { \
        pushException("Not file handle"); \
        return 0; \
    } else { \
        _name_ = _s_ptr.get(); \
    }


size_t readFile(std::string& file, char **buf) {
    FILE* fd = 0;
    if (fopen_s(&fd, file.c_str(), "rb")) {
        return 0;
    }
    
    LocalResource<FILE, int> close(fd, fclose);
    fseek(fd, 0, SEEK_END);
    int len = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    *buf = new char[len];
    size_t rlen = fread(*buf, sizeof(char), len, fd);
    return rlen;
}


size_t readTxtFile(std::string& fileName, std::string &content) {
    char *buf = 0;
    size_t len = readFile(fileName, &buf);
    if (len > 0) {
        content.append(buf, len);
    }
    if (buf) delete[] buf;
    return len;
}


template<>
class SharedResourceDeleter<FILE> {
public:
    virtual void operator()(FILE* fd) {
        // println("FILE closed", 0, LDEBUG);
        fclose(fd);
    }
};


JS_FUNC_TPL(js_open, c, args, ac, info, d) {
    if (ac != 3) {
        pushException("bad arguments length, open(path, mode)");
        return 0;
    }
    auto path = stringValue(args[1]);
    auto flag = stringValue(args[2]);

    FILE* fd = 0;
    if (fopen_s(&fd, path.c_str(), flag.c_str())) {
        pushException("open file fail "+ path);
        return 0;
    }
    int handle = make_shared_handle(fd);
    return wrapJs(handle);
}


JS_FUNC_TPL(js_close, c, args, ac, info, d) {
    if (ac != 2) {
        pushException("bad arguments length, close(fd)");
        return 0;
    }
    GET_FD_FROM_JS(fd, args[1]);
    release_shared_resource<FILE>(_handle);
    return 0;
}


JS_FUNC_TPL(js_read, c, args, ac, info, d) {
    if (ac != 6 && ac != 5) {
        pushException("bad arguments, read(fd, buffer, b_offset, b_length, f_pos)");
        return 0;
    }
    GET_FD_FROM_JS(fd, args[1]);
    LocalTypedArray arr(args[2]);
    unsigned int b_offset = intValue(args[3], 0);
    unsigned int b_length = intValue(args[4], arr.length());

    b_offset = max(0, min(b_offset, arr.length()));
    b_length = max(0, min(arr.length() - b_offset, b_length));
    
    if (ac == 6 && isJsNumber(args[5])) {
        int pos = intValue(args[5]);
        fseek(fd, pos, SEEK_SET);
    }
    int rlen = fread(arr.buffer()+b_offset, 1, b_length, fd);
    return wrapJs(rlen);
}


JS_FUNC_TPL(js_write, c, args, ac, info, d) {
    if (ac != 6 && ac != 5) {
        pushException("bad arguments, write(fd, buffer, b_offset, b_length, f_pos)");
        return 0;
    }
    GET_FD_FROM_JS(fd, args[1]);
    LocalTypedArray arr(args[2]);
    unsigned int b_offset = intValue(args[3]);
    unsigned int b_length = intValue(args[4]);

    b_offset = max(0, min(b_offset, arr.length()));
    b_length = max(0, min(arr.length() - b_offset, b_length));

    if (ac == 6 && isJsNumber(args[5])) {
        int pos = intValue(args[5]);
        fseek(fd, pos, SEEK_SET);
    }
    int wlen = fwrite(arr.buffer()+b_offset, 1, b_length, fd);
    return wrapJs(wlen);
}


JS_FUNC_TPL(js_file_size, c, args, ac, info, d) {
    if (ac != 2) {
        pushException("bad arguments, fileSize(filename)");
        return 0;
    }
    std::string filename = toString(args[1]);
    try {
      return wrapJs((int) fs::file_size(filename));
    } catch(fs::filesystem_error& err) {
      pushException(err.what());
      return 0;
    }
}


JS_FUNC_TPL(js_fpos, c, args, ac, info, d) {
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


JS_FUNC_TPL(js_exists, c, args, ac, info, d) {
    JSS_CHK_ARG(1, exists(path));
    auto filename = stringValue(args[1]);
    bool ex = fs::exists(filename);
    return wrapJs(ex);
}


JSS_FUNC(read_txt, args, ac) {
    JSS_CHK_ARG(1, read_txt(path));
    auto filename = stringValue(args[1]);
    char *buf;
    int rlen = readFile(filename, &buf);
    if (rlen <= 0) {
        pushException("Read string from file failed: "+ filename);
        return 0;
    }
    std::unique_ptr<char[]> ptr(buf);
    return wrapJs(buf, rlen);
}


JSS_FUNC(read_dir, args, ac) {
    JSS_CHK_ARG(1, read_dir(path));
    auto dirname = stringValue(args[1]);
    if (! fs::is_directory(dirname)) {
        pushException(dirname +" is not directory");
        return 0;
    }
    LocalArray files;
    for (auto& it : fs::directory_iterator(dirname)) {
        std::string dir = it.path().string();
        files.push( wrapJs(dir.c_str(), dir.size()) );
    }
    return files;
}


void installFileSystem(VM *vm) {
    DEF_GLOBAL(vm, fs);

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

    LocalVal fpos = vm->createFunction(&js_fpos, "fpos", vm);
    fs.put("fpos", fpos);
    fs.put("fposSync", fpos);

    DEF_JS_FUNC(vm, vm, fs, fileSize, js_file_size);
    DEF_JS_FUNC(vm, vm, fs, exists, js_exists);
    DEF_JS_FUNC(vm, vm, fs, read_txt, js_read_txt);
    DEF_JS_FUNC(vm, vm, fs, read_dir, js_read_dir);
}