#include "headers/Slab.h"
#include <iostream>

template<typename T> Slab<T>::Slab(size_t c_slabsize): slabsize(c_slabsize), usedSlots(0){
    memoryArray = new T[slabsize];
    freeSlots = new bool[slabsize];
    
    for(int iter=0;iter<slabsize;iter++){
        freeSlots[iter] = false;
    }
}

template<typename T> Slab<T>::~Slab(){
    delete[] memoryArray;
    delete[] freeSlots;
}

template<typename T> T* Slab<T>::allocate(){
    if(usedSlots < slabsize){
        for(int iter=0;iter<slabsize;iter++){
            if(!freeSlots[iter]){
                freeSlots = true;
                usedSlots++;
                std::cout << "Allocated the memory" << std::endl;
                return new(&memoryArray[iter]) T();;
            }
        }
    }
    return nullptr;
}

template<typename T> void Slab<T>::deallocate(T* ptr){
    int index = ptr-memoryArray;
    if(index >= 0 && index < slabsize){
        freeSlots[index] = false;
        usedSlots--;
        std::cout << "De allocated the memory" << std::endl;
        return;
    }
    else std::cout << "Error in deallocating" << std::endl;
}

template<typename T> bool Slab<T>::contains(T* ptr){
    int index = ptr-memoryArray;
    return index >= 0 && index < slabsize;
}