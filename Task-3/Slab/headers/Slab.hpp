#pragma once
#include<iostream>
#include"./MyClass.hpp"

class Slab{

    private:
        MyClass* memoryArray;
        bool* freeSlots;
        size_t slabsize;
        size_t usedSlots;

    public:
        explicit Slab(size_t c_slabsize = 10);
        ~Slab();

        MyClass* allocate(std::string name);
        void deallocate(MyClass* ptr);
        bool contains(MyClass* ptr);
};

Slab::Slab(size_t c_slabsize): slabsize(c_slabsize), usedSlots(0){
    memoryArray = static_cast<MyClass*>(std::malloc(sizeof(MyClass) * slabsize));
    freeSlots = new bool[slabsize];
    
    for(int iter=0;iter<slabsize;iter++){
        freeSlots[iter] = false;
    }
}

Slab::~Slab(){
    delete[] memoryArray;
    delete[] freeSlots;
}

MyClass* Slab::allocate(std::string name){
    if(usedSlots < slabsize){
        for(int iter=0;iter<slabsize;iter++){
            if(!freeSlots[iter]){
                freeSlots[iter] = true;
                usedSlots++;
                std::cout << "Allocated the memory" << std::endl;
                return new(&memoryArray[iter]) MyClass(name);;
            }
        }
    }
    return nullptr;
}

void Slab::deallocate(MyClass* ptr){
    int index = ptr-memoryArray;
    if(index >= 0 && index < slabsize){
        freeSlots[index] = false;
        usedSlots--;
        std::cout << "De allocated the memory" << std::endl;
        return;
    }
    else std::cout << "Error in deallocating" << std::endl;
}

bool Slab::contains(MyClass* ptr){
    int index = ptr-memoryArray;
    return index >= 0 && index < slabsize;
}