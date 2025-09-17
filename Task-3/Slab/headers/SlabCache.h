#pragma once
#include<vector>
#include"Slab.h"

template<typename T>
class SlabCache{
    private:
        std::vector<Slab<T>> vectorOfSlabs;

    public:
        T* allocate();
        void deallocate(T* ptr);
};