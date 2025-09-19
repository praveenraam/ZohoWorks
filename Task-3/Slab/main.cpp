#include<iostream>
#include "./headers/SlabAllocator.hpp"
#include "./headers/MyClass.hpp"
#include "./headers/HerClass.hpp"

int main(){
    MemoryManage* main_memory_manager = MemoryManage::getMemoryManageObj();
    SlabAllocator* obj = SlabAllocator::getInstance();

    MyClass* m1 = obj->sa_allocate<MyClass>();
    MyClass* m2 = obj->sa_allocate<MyClass>();
    MyClass* m3 = obj->sa_allocate<MyClass>();
    MyClass* m4 = obj->sa_allocate<MyClass>();
    MyClass* m5 = obj->sa_allocate<MyClass>();
    MyClass* m6 = obj->sa_allocate<MyClass>();
    MyClass* m7 = obj->sa_allocate<MyClass>();
    MyClass* m8 = obj->sa_allocate<MyClass>();
    MyClass* m9 = obj->sa_allocate<MyClass>();
    MyClass* m10 = obj->sa_allocate<MyClass>();
    MyClass* m11 = obj->sa_allocate<MyClass>();
    MyClass* m12 = obj->sa_allocate<MyClass>();

    std::cout << "-------------------------------------------------------------------------------------------" << std::endl;

    HerClass* h1 = obj->sa_allocate<HerClass>();
    HerClass* h2 = obj->sa_allocate<HerClass>();

    std::cout << "-------------------------------------------------------------------------------------------" << std::endl;

    std::cout << "m5 : " << m5 << std::endl;
    obj->sa_deallocate<MyClass>(m5);

    std::cout << "m8 : " << m8 << std::endl;
    obj->sa_deallocate<MyClass>(m8);

    MyClass* m13 = obj->sa_allocate<MyClass>();
    MyClass* m14 = obj->sa_allocate<MyClass>();

    std::cout << "m13 & m14 : " << m13 << " & " << m14 << std::endl;

    std::cout << "-------------------------------------------------------------------------------------------" << std::endl;

    obj->sa_deallocate<HerClass>(h1);

    std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
    
    std::cout << sizeof(MyClass) << " " << sizeof(HerClass) << std::endl;
    std::cout << "MyClass Object occupied space: " << obj->AllocatorGetCacheMemoryUsage<MyClass>() << std::endl;

    std::cout << "HerClass Object occupied space: " <<  obj->AllocatorGetCacheMemoryUsage<HerClass>() << std::endl;
    std::cout << "Total Memory occupied by Program:" << main_memory_manager->getMemoryUsed() << std::endl;

}