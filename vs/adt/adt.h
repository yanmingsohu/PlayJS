#pragma once

#define BIO2_ADT_EXT
#pragma comment(lib, "adt.lib")

//
// out 和 outlen 在下次调用会失效
// 该方法线程不安全
//
void unpackImage(unsigned char *source, int length, unsigned char** out, int *outlen);