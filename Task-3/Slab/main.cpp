#include<iostream>
#include "./headers/SlabAllocator.hpp"
#include "./headers/MyClass.hpp"
#include "./headers/HerClass.hpp"

int main(){
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
    MyClass* m13 = obj->sa_allocate<MyClass>();
    MyClass* m14 = obj->sa_allocate<MyClass>();

    std::cout << "m3 : " << m3 << std::endl;
    obj->sa_deallocate<MyClass>(m3);

    std::cout << "m4 : " << m4 << std::endl;
    obj->sa_deallocate<MyClass>(m4);

    MyClass* m11 = obj->sa_allocate<MyClass>();
    MyClass* m12 = obj->sa_allocate<MyClass>();

    std::cout << "m11 & m12 : " << m11 << " & " << m12 << std::endl;

    obj->printMap();
}