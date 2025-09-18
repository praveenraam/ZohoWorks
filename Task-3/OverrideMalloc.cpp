#include "OverrideMalloc.h"
#include "./Slab/headers/SlabAllocator.hpp"

MemoryManage* MemoryManage::getMemoryManageObj(){
    // if(mtx == nullptr) mtx = new std::mutex;
    mtx->lock();
        if(obj == nullptr) obj = new MemoryManage();
    mtx->unlock();
    return obj; 
}

void MemoryManage::AddMemory(void* ptr,int size){
    mtx->lock();
        memoryUsedByProgram+=size;
        mapForSize.insert({ptr,size});
        std::cout << "At add : " << memoryUsedByProgram << std::endl;
    mtx->unlock();  
}

void MemoryManage::removeMemory(void* ptr){
    auto iter = mapForSize.find(ptr);

    mtx->lock();
        if(iter != mapForSize.end()){
            memoryUsedByProgram = memoryUsedByProgram - (iter->second);
            mapForSize.erase(iter);
            std::cout << "At remove : " << memoryUsedByProgram << std::endl;
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


void create_and_dest_array(){
    int* arr = (int*)ud_malloc(4*sizeof(int));

    for(int iter=0;iter<4;iter++){
        arr[iter] = iter*iter;
        // std::cout << arr[iter] << std::endl;
    }
    ud_free(arr);
}

int main(){
    MemoryManage* memoryManage = MemoryManage::getMemoryManageObj();
    std::cout << "Used Memory from Memory Manage at begin : " << memoryManage->getMemoryUsed() << std::endl;

    std::thread t1(create_and_dest_array);
    std::thread t2(create_and_dest_array);
    std::thread t3(create_and_dest_array);
    
    t1.join(); t2.join(); t3.join();
}