#pragma once

#include <iostream>
#include<stdio.h>

constexpr int FAILED = -1;


class FileSystem {
};


//
// 读取文件成功返回缓冲区长度, 失败返回 -1
//
int readFile(std::string file, char **buf);


int readTxtFile(std::string fileName, std::string &content);