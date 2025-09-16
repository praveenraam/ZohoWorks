#pragma once
#include<iostream>
#include <malloc.h>
#include <stdlib.h>
#include <map>

class MemoryManage{
private:
    size_t memoryUsedByProgram;
    static MemoryManage* obj;
    std::map<void*,size_t> mapForSize;
    MemoryManage(): memoryUsedByProgram(0){}

public :
    static MemoryManage* getMemoryManageObj();
    void AddMemory(void* ptr,int size);
    void removeMemory(void* ptr);
    size_t getMemoryUsed();
};