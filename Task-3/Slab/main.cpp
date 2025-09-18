#include<iostream>
#include "./headers/SlabAllocator.hpp"
#include "./headers/MyClass.hpp"
#include "./headers/HerClass.hpp"

int main(){
    SlabAllocator* obj = SlabAllocator::getInstance();

    HerClass* m1 = obj->sa_allocate<HerClass>();

    MyClass* m2 = obj->sa_allocate<MyClass>();

    m2->sayHello();
    m1->sayHello();

    obj->sa_deallocate<HerClass>(m1);

    obj->sa_deallocate<MyClass>(m2);
    obj->printMap();
}