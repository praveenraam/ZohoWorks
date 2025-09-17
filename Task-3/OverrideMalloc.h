#pragma once
#include<iostream>
#include <malloc.h>
#include <stdlib.h>
#include <map>
#include <mutex>
#include <thread>

class MemoryManage{
private:
    size_t memoryUsedByProgram;
    static MemoryManage* obj;
    static std::mutex* mtx;
    std::map<void*,size_t> mapForSize;
    MemoryManage(): memoryUsedByProgram(0){}
    
public :    
    static MemoryManage* getMemoryManageObj();
    void AddMemory(void* ptr,int size);
    void removeMemory(void* ptr);
    size_t getMemoryUsed();
    ~MemoryManage();
};

void* ud_malloc(std::size_t size);
void ud_free(void* ptr);