#pragma once

#include <iostream>
#include<stdio.h>

constexpr int FAILED = -1;


class FileSystem {
};


//
// ��ȡ�ļ��ɹ����ػ���������, ʧ�ܷ��� -1
//
int readFile(std::string file, char **buf);


int readTxtFile(std::string fileName, std::string &content);