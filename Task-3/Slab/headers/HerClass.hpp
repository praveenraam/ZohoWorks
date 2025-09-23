#pragma once
#include<iostream>
#include<string>

class HerClass { // Removed the std::string name for reducing the size of the class -- 1byte of memory for each object
public:

    HerClass() { 
        // std::cout << "HerClass created! " << std::endl;     
    }
    
    ~HerClass() { 
        // std::cout << "HerClass destroyed!" << std::endl; 
    }
    
    void sayHello() {
        std::cout << "Hello from Herclass! " << std::endl; 
    }
};
