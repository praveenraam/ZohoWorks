#pragma once
#include<iostream>
// #include"./MyClass.hpp"

template <typename T>
class Slab{

    private:
        T* memoryArray;
        bool* freeSlots;
        size_t slabsize;
        size_t usedSlots;

    public:
        explicit Slab(size_t c_slabsize = 10);
        ~Slab();

        T* allocate();
        void deallocate(T* ptr);
        bool contains(T* ptr);
};

template <typename T>
Slab<T>::Slab(size_t c_slabsize): slabsize(c_slabsize), usedSlots(0){
    memoryArray = static_cast<T*>(std::malloc(sizeof(T) * slabsize));
    freeSlots = new bool[slabsize];
    
    for(int iter=0;iter<slabsize;iter++){
        freeSlots[iter] = false;
    }
}

template <typename T>
Slab<T>::~Slab(){
    for (size_t iter = 0; iter < slabsize; iter++) {
        if (freeSlots[iter]) {
            // memoryArray[iter]~T();
        }
    }

    delete[] memoryArray;
    delete[] freeSlots;
}

template <typename T>
T* Slab<T>::allocate(){
    if(usedSlots < slabsize){
        for(int iter=0;iter<slabsize;iter++){
            if(!freeSlots[iter]){
                freeSlots[iter] = true;
                usedSlots++;
                std::cout << "Allocated the memory" << std::endl;
                return new(&memoryArray[iter]) T();
            }
        }
    }
    return nullptr;
}

template <typename T>
void Slab<T>::deallocate(T* ptr){
    int index = ptr-memoryArray;
    if(index >= 0 && index < slabsize){
        freeSlots[index] = false;
        ptr->~T();
        usedSlots--;
        std::cout << "De allocated the memory" << std::endl;
        return;
    }
    else std::cout << "Error in deallocating" << std::endl;
}

template <typename T>
bool Slab<T>::contains(T* ptr){
    int index = ptr-memoryArray;
    return index >= 0 && index < slabsize;
}