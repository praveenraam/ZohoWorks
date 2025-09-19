#include <iostream>
#include "./headers/SlabAllocator.hpp"
#include "./headers/MyClass.hpp"
#include "./headers/HerClass.hpp"

// Define new test classes right here in main.cpp
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

int main() {
    MemoryManage* main_memory_manager = MemoryManage::getMemoryManageObj();
    SlabAllocator* obj = SlabAllocator::getInstance();

    std::cout << "\n=== Allocations for MyClass and HerClass ===\n";
    MyClass* my1 = obj->sa_allocate<MyClass>();
    HerClass* her1 = obj->sa_allocate<HerClass>();

    std::cout << "MyClass ptr: " << my1 << "\n";
    std::cout << "HerClass ptr: " << her1 << "\n";

    std::cout << "\n=== Allocations for HisClass and TheirClass ===\n";
    HisClass* his1 = obj->sa_allocate<HisClass>();
    TheirClass* their1 = obj->sa_allocate<TheirClass>();

    std::cout << "HisClass ptr: " << his1 << "\n";
    std::cout << "TheirClass ptr: " << their1 << "\n";

    his1->print();
    their1->print();

    std::cout << "\n=== Deallocation and Reallocation Tests ===\n";
    obj->sa_deallocate<MyClass>(my1);
    obj->sa_deallocate<HerClass>(her1);
    obj->sa_deallocate<HisClass>(his1);
    obj->sa_deallocate<TheirClass>(their1);

    MyClass* my2 = obj->sa_allocate<MyClass>();
    HerClass* her2 = obj->sa_allocate<HerClass>();
    HisClass* his2 = obj->sa_allocate<HisClass>();
    TheirClass* their2 = obj->sa_allocate<TheirClass>();

    std::cout << "Reallocated MyClass ptr: " << my2 << "\n";
    std::cout << "Reallocated HerClass ptr: " << her2 << "\n";
    std::cout << "Reallocated HisClass ptr: " << his2 << "\n";
    std::cout << "Reallocated TheirClass ptr: " << their2 << "\n";

    std::cout << "\n=== Edge Cases: Double Free and Free Invalid Pointer ===\n";
    obj->sa_deallocate<MyClass>(my2);
    obj->sa_deallocate<MyClass>(my2); 

    std::cout << "\n=== Memory Usage ===\n";
    std::cout << "MyClass memory usage: " << obj->AllocatorGetCacheMemoryUsage<MyClass>() << " bytes\n";
    std::cout << "HerClass memory usage: " << obj->AllocatorGetCacheMemoryUsage<HerClass>() << " bytes\n";
    std::cout << "HisClass memory usage: " << obj->AllocatorGetCacheMemoryUsage<HisClass>() << " bytes\n";
    std::cout << "TheirClass memory usage: " << obj->AllocatorGetCacheMemoryUsage<TheirClass>() << " bytes\n";

    std::cout << "Total program memory used: " << main_memory_manager->getMemoryUsed() << " bytes\n";

    return 0;
}
