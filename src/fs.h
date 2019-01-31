#pragma once

#include<iostream>
#include<stdio.h>

constexpr int FAILED = -1;


//
// 读取文件成功返回缓冲区长度, 失败返回 -1
//
int readFile(std::string& file, char **buf);


//
// 读取文本文件(utf8)成功返回缓冲区长度, 失败返回 -1
//
int readTxtFile(std::string& fileName, std::string& content);