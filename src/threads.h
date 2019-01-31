#pragma once

#include "vm.h"
#include <thread>

typedef int threadId;

//
// 在当前线程加载并运行脚本
//
void loadScript(std::string& filename, threadId id = 0);

//
// 在新的线程中加载并启动脚本
//
threadId loadScriptInNewThread(std::string& fileName);

//
// 返回线程
//
std::thread* getThread(threadId i);

//
// 等待所有线程结束后返回
//
void joinAll();