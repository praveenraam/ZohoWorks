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
    
public :    
    static MemoryManage* getMemoryManageObj();
    void AddMemory(void* ptr,int size);
    void removeMemory(void* ptr);
    size_t getMemoryUsed();

    MemoryManage(): memoryUsedByProgram(0){}
    ~MemoryManage();
};

void* ud_malloc(std::size_t size);
void ud_free(void* ptr);
void* ud_malloc(std::size_t size,MemoryManage* manager);
void ud_free(void* ptr,MemoryManage* manager);

MemoryManage* MemoryManage::getMemoryManageObj() {
    static MemoryManage instance;
    return &instance;
}

void MemoryManage::AddMemory(void* ptr,int size){
    mtx->lock();
        memoryUsedByProgram+=size;
        mapForSize.insert({ptr,size});
        // std::cout << "At add : " << memoryUsedByProgram << std::endl;
    mtx->unlock();  
}

void MemoryManage::removeMemory(void* ptr){
    auto iter = mapForSize.find(ptr);

    mtx->lock();
        if(iter != mapForSize.end()){
            memoryUsedByProgram = memoryUsedByProgram - (iter->second);
            mapForSize.erase(iter);
            // std::cout << "At remove : " << memoryUsedByProgram << std::endl;
        }
        else std::cout << "ptr in param is not found" << std::endl;
    mtx->unlock();
}

size_t MemoryManage::getMemoryUsed(){
    return memoryUsedByProgram;
}

MemoryManage::~MemoryManage(){
    delete mtx;
    delete obj;
}

std::mutex* MemoryManage::mtx = new std::mutex(); // Initializing before the main
MemoryManage* MemoryManage::obj = nullptr;


void* ud_malloc(std::size_t size){
    void* address = malloc(size);

    if(address == nullptr){
        return nullptr;
    }

    MemoryManage* memoryManage = MemoryManage::getMemoryManageObj();
    memoryManage->AddMemory(address,size);

    return address;
}

void ud_free(void* ptr){    

    MemoryManage* memoryManage = MemoryManage::getMemoryManageObj();
    memoryManage->removeMemory(ptr);

    free(ptr);
}