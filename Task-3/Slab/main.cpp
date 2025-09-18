#include<iostream>
#include "./headers/SlabAllocator.hpp"

int main(){
    SlabAllocator* obj = SlabAllocator::getInstance();
    std::string name = "M1";
    MyClass* m1 = obj->allocate(name);
    name = "M2";
    MyClass* m2 = obj->allocate(name);

    m2->sayHello();
    m1->sayHello();

    name = "M3";
    obj->deallocate(m1);

    MyClass* m3 = obj->allocate("M3");
    m1->sayHello();

    obj->printMap();
}