#pragma once
#include<iostream>

enum class StatusOfSlotsAvailable{
    EMPTY,
    PARTIAL,
    FULL
};

template <typename T>
class Slab{

    private:
        T* memoryArray;
        bool* freeSlots;
        StatusOfSlotsAvailable status;
        size_t slabsize;
        size_t usedSlots;

    public:
        explicit Slab(size_t c_slabsize = 10);
        ~Slab();

        T* sb_allocate();
        void sb_deallocate(T* ptr);
        bool contains(T* ptr);
        StatusOfSlotsAvailable getStatus();
};

template <typename T> Slab<T>::Slab(size_t c_slabsize): slabsize(c_slabsize), usedSlots(0), status(StatusOfSlotsAvailable::EMPTY){
    memoryArray = static_cast<T*>(std::malloc(sizeof(T) * slabsize));
    freeSlots = new bool[slabsize];
    
    for(int iter=0;iter<slabsize;iter++){
        freeSlots[iter] = false;
    }
}

template <typename T> Slab<T>::~Slab(){
    for (size_t iter = 0; iter < slabsize; iter++) {
        if (freeSlots[iter]) {
            // memoryArray[iter]~T();
        }
    }

    delete[] memoryArray;
    delete[] freeSlots;
}

template <typename T> T* Slab<T>::sb_allocate(){
    if(status != StatusOfSlotsAvailable::FULL){
        for(int iter=0;iter<slabsize;iter++){
            if(!freeSlots[iter]){
                freeSlots[iter] = true;
                usedSlots++;
                status = StatusOfSlotsAvailable::PARTIAL;
                if(usedSlots == slabsize) status = StatusOfSlotsAvailable::FULL;

                std::cout << "Allocated the memory" << std::endl;
                return new(&memoryArray[iter]) T();
            }
        }
    }
    return nullptr;
}

template <typename T> void Slab<T>::sb_deallocate(T* ptr){
    int index = ptr-memoryArray;
    if(index >= 0 && index < slabsize){
        ptr->~T(); // What to do here.
        // delete ptr;
        freeSlots[index] = false;
        usedSlots--;
        std::cout << "De allocated the memory" << std::endl;

        if(usedSlots == 0) status = StatusOfSlotsAvailable::EMPTY;

        return;
    }
    else std::cout << "Error in deallocating" << std::endl;
}

template <typename T> bool Slab<T>::contains(T* ptr){
    int index = ptr-memoryArray;
    return index >= 0 && index < slabsize;
}

template <typename T> StatusOfSlotsAvailable Slab<T>::getStatus() {
    return status;
}
