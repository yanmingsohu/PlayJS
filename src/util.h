#pragma once

#include <string>
#include <iostream>
#include "threads.h"

//
// log levels
//
const int LINFO = 1;
const int LERROR = 2;
const int LWARN = 3;
const int LDEBUG = 4;
const int LFATAL = 5;

//
// 将输入的 gbk 字节序列串转换为 utf8 字符串
// 实现在 utf.cpp
//
void gbk2utf8(char* from, int fromLenth, std::string &out);


//
// 输出字符串到控制台, 可以正确处理中文编码
// 实现在 console.cpp
//
void println(const char *src_str, threadId id = 0, int level = LINFO);
void println(const std::string str, threadId id = 0, int level = LINFO);


//
// 局部范围资源引用句柄, 函数返回后释放
//
template<class FreeType, class RetType = void>
class LocalResource {
    typedef RetType(*FreeFunction)(FreeType*);

private:
    FreeType *_res;
    FreeFunction _func;

    LocalResource(LocalResource&);

public:
    LocalResource(FreeType *resource, FreeFunction f)
    : _res(resource), _func(f) {
    }

    virtual ~LocalResource() {
        _func(_res);
    }

    FreeType* operator->() {
        return _res;
    }
};


template<class T>
void DeletePoint(T* p) {
    delete p;
}


template<class T>
void DeleteArray(T* arr) {
    delete [] arr;
}


class Welcome {
public:
    Welcome() {
        std::cout 
<< "\n---------------------------------------------------------------------------"
<< "\n>>>>>                  PlayJS Game Engine Start...                    <<<<<"
<< "\n---------------------------------------------------------------------------"
<< std::endl;
    }

    ~Welcome() {
        std::cout << "\n"
<< "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<< PlayJS Exit >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" 
<< std::endl;
    }
};