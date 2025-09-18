#pragma once
#include<iostream>
#include<string>

class MyClass {
private:
    std::string name;
public:

    MyClass(std::string name) { 
        std::cout << "MyClass created! " << std::endl; 
        this->name = name;
    }
    
    ~MyClass() { 
        std::cout << "MyClass destroyed!" << std::endl; 
    }
    
    void sayHello() {
        std::cout << "Hello from class! " << this->name << std::endl; 
    }
};
