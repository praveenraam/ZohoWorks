#pragma once

#include<iostream>

template<typename T>
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