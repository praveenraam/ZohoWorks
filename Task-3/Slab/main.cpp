#include<iostream>
#include "./headers/SlabAllocator.h"

class MyClass {
public:
    MyClass() { 
        std::cout << "MyClass created!" << std::endl; 
    }
    
    ~MyClass() { 
        std::cout << "MyClass destroyed!" << std::endl; 
    }
    
    void sayHello() {
        std::cout << "Hello from MyClass!" << std::endl;
    }
};

int main(){
    SlabAllocator* obj = SlabAllocator::getInstance();

    MyClass* m1 = obj->allocate<MyClass>();
    MyClass* m2 = obj->allocate<MyClass>();

    m2->sayHello();
    m1->sayHello();
}