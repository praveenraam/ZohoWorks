#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
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

void threadFunction(SlabAllocator* allocatorObj){

    MyClass* my1 = allocatorObj->sa_allocate<MyClass>();
    HerClass* her1 = allocatorObj->sa_allocate<HerClass>();
    HisClass* his1 = allocatorObj->sa_allocate<HisClass>();
    TheirClass* their1 = allocatorObj->sa_allocate<TheirClass>();

    {
        std::lock_guard<std::mutex> lock(mutex_print);
            std::cout << "MyClass : " << my1 << std::endl;
            std::cout << "HerClass : " << her1 << std::endl;
            std::cout << "HisClass : " << his1 << std::endl;
            std::cout << "TheirClass : " << their1 << std::endl;
    }
    
    allocatorObj->sa_deallocate<MyClass>(my1);
    allocatorObj->sa_deallocate<HerClass>(her1);
    allocatorObj->sa_deallocate<HisClass>(his1);
    allocatorObj->sa_deallocate<TheirClass>(their1);

    {
        std::lock_guard<std::mutex> lock(mutex_print);
            std::cout << "Thread No : " << std::this_thread::get_id() << " completed the execution" << std::endl;
    }

}

int main(){

    MemoryManage* memory_manager = MemoryManage::getMemoryManageObj();
    SlabAllocator* allocatorObj = SlabAllocator::getInstance();
    
    int countOfThreads = 20;
    int countOfIteration = 4;

    std::vector<std::thread> threads1;
    for(int iter=0;iter<countOfThreads;iter++){
        threads1.emplace_back(threadFunction,allocatorObj);
    }

    for(std::thread& thread_iter : threads1){
        thread_iter.join();
    }

    std::vector<std::thread> threads2;
    for(int iter=0;iter<countOfThreads/2;iter++){
        threads2.emplace_back(threadFunction,allocatorObj);
    }

    for(std::thread& thread_iter : threads2){
        thread_iter.join();
    }
}