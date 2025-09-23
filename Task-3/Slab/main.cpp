#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <fstream>
#include "./headers/SlabAllocator.hpp"
#include "./headers/MyClass.hpp"
#include "./headers/HerClass.hpp"

class HisClass {
public:
    int x, y;
    HisClass() : x(0), y(0) {}
    void print() { std::cout << "HisClass: (" << x << "," << y << ")\n"; }
};

class TheirClass {
public:
    double d;
    TheirClass() : d(3.14159) {}
    void print() { std::cout << "TheirClass: " << d << "\n"; }
};

std::mutex mutex_print;

void threadFunction(SlabAllocator* allocatorObj,MemoryManage* memory_manager){

    MyClass* my1 = allocatorObj->sa_allocate<MyClass>();
    HerClass* her1 = allocatorObj->sa_allocate<HerClass>();
    HisClass* his1 = allocatorObj->sa_allocate<HisClass>();
    TheirClass* their1 = allocatorObj->sa_allocate<TheirClass>();

    {
        std::lock_guard<std::mutex> lock(mutex_print);
        
            std::ofstream out("output.txt", std::ios::app);

            if(out.is_open()){
                out << "MyClass : " << my1 << " : Memory used by MyClass : " << allocatorObj->AllocatorGetCacheMemoryUsage<MyClass>() << std::endl;
                out << "HerClass : " << her1 << " : Memory used by HerClass : " << allocatorObj->AllocatorGetCacheMemoryUsage<HerClass>() << std::endl;
                out << "HisClass : " << his1 << " : Memory used by HisClass : " << allocatorObj->AllocatorGetCacheMemoryUsage<HisClass>() << std::endl;
                out << "TheirClass : " << their1 << " : Memory used by TheirClass : " << allocatorObj->AllocatorGetCacheMemoryUsage<TheirClass>() << std::endl;
                out << "Total Memory used by the Program : " << memory_manager->getMemoryUsed() << " \n" << std::endl;
            }
        }
    
    allocatorObj->sa_deallocate<MyClass>(my1);
    allocatorObj->sa_deallocate<HerClass>(her1);
    allocatorObj->sa_deallocate<HisClass>(his1);
    allocatorObj->sa_deallocate<TheirClass>(their1);

}

int main(){

    MemoryManage* memory_manager = MemoryManage::getMemoryManageObj();
    SlabAllocator* allocatorObj = SlabAllocator::getInstance();
    std::ofstream("output.txt", std::ios::trunc).close();
    
    int countOfThreads = 100;

    std::vector<std::thread> threads1;
    for(int iter=0;iter<countOfThreads;iter++){
        threads1.emplace_back(threadFunction,allocatorObj,memory_manager);
    }

    for(std::thread& thread_iter : threads1){
        thread_iter.join();
    }

    std::vector<std::thread> threads2;
    for(int iter=0;iter<countOfThreads/2;iter++){
        threads2.emplace_back(threadFunction,allocatorObj,memory_manager);
    }

    for(std::thread& thread_iter : threads2){
        thread_iter.join();
    }

    std::ofstream outputFile("output.txt", std::ios::app);
    if (outputFile.is_open()) {
        outputFile << "\n--- Final Summary ---\n";
        outputFile << "Memory used by MyClass : " << allocatorObj->AllocatorGetCacheMemoryUsage<MyClass>() << std::endl;
        outputFile << "Memory used by HerClass : " << allocatorObj->AllocatorGetCacheMemoryUsage<HerClass>() << std::endl;
        outputFile << "Memory used by HisClass : " << allocatorObj->AllocatorGetCacheMemoryUsage<HisClass>() << std::endl;
        outputFile << "Memory used by TheirClass : " << allocatorObj->AllocatorGetCacheMemoryUsage<TheirClass>() << std::endl;
        outputFile << "Total Memory used by the Program : " << memory_manager->getMemoryUsed() << " \n" << std::endl;
    }

}