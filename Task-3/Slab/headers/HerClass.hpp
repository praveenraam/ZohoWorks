#pragma once
#include<iostream>
#include<string>

class HerClass {
private:
    std::string name;
public:

    HerClass() { 
        std::cout << "HerClass created! " << std::endl; 
    }
    
    ~HerClass() { 
        std::cout << "HerClass destroyed!" << std::endl; 
    }
    
    void sayHello() {
        std::cout << "HerClass from class! " << std::endl; 
    }
};
