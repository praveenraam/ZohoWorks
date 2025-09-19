#pragma once
#include<iostream>
#include <cstdlib>
#include <stdlib.h>
#include <map>
#include <mutex>
#include <thread>

class MemoryManage{
private:
    size_t memoryUsedByProgram;
    std::mutex mtx;
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

MemoryManage* MemoryManage::getMemoryManageObj() {
    static MemoryManage instance;
    return &instance;
}

void MemoryManage::AddMemory(void* ptr,int size){

    if(ptr == nullptr || size == 0){
        return;
    }

    std::lock_guard<std::mutex> lock(mtx);
        memoryUsedByProgram+=size;
        mapForSize.insert({ptr,size});
        // std::cout << "At add : " << memoryUsedByProgram << std::endl;
}

void MemoryManage::removeMemory(void* ptr){

    if(ptr == nullptr){
        return;
    }

    std::lock_guard<std::mutex> lock(mtx);
        auto iter = mapForSize.find(ptr);

        if(iter != mapForSize.end()){
            memoryUsedByProgram = memoryUsedByProgram - (iter->second);
            mapForSize.erase(iter);
            // std::cout << "At remove : " << memoryUsedByProgram << std::endl;
        }
        else std::cout << "ptr in param is not found" << std::endl;
}

size_t MemoryManage::getMemoryUsed(){
    std::lock_guard<std::mutex> lock(mtx);
        return memoryUsedByProgram;
}

MemoryManage::~MemoryManage(){
}

// std::mutex* MemoryManage::mtx = new std::mutex(); // Initializing before the main
// MemoryManage* MemoryManage::obj = nullptr;


void* ud_malloc(std::size_t size){

    if(size == 0){
        return nullptr;
    }

    void* address = std::malloc(size);

    if(address == nullptr){
        return nullptr;
    }

    MemoryManage* memoryManage = MemoryManage::getMemoryManageObj();
    memoryManage->AddMemory(address,size);

    return address;
}

void ud_free(void* ptr){    

    if(ptr == nullptr) return;

    MemoryManage* memoryManage = MemoryManage::getMemoryManageObj();
    memoryManage->removeMemory(ptr);

    std::free(ptr);
}