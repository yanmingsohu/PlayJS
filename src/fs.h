#pragma once

#include <string>

constexpr int FAILED = -1;


//
// 读取文件成功返回缓冲区长度, 失败返回 0,
// 返回的内存需要自行释放.
//
size_t readFile(std::string& file, char **buf);


//
// 读取文本文件(utf8)成功返回缓冲区长度, 失败返回 0,
// 不需要释放内存的操作
//
size_t readTxtFile(std::string& fileName, std::string& content);