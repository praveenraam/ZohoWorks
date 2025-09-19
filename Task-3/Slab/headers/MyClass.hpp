#pragma once
#include<iostream>
#include<string>

class MyClass { // 32 byte of memory for each object
private:
    std::string name;
public:

    MyClass() { 
        std::cout << "MyClass created! " << std::endl; 
    }
    
    ~MyClass() { 
        std::cout << "MyClass destroyed!" << std::endl; 
    }
    
    void sayHello() {
        std::cout << "Hello from class! " << this->name << std::endl; 
    }
};
