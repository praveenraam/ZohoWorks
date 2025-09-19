#pragma once
#include<vector>
#include<stack>
#include"Slab.hpp"

template <typename T>
class SlabCache{
    private:
        std::vector<Slab<T>*> vectorOfSlabs;
        std::stack<Slab<T>*> free_slabs_st;
    public:
        T* sc_allocate();
        void sc_deallocate(T* ptr);
};

template <typename T>
T* SlabCache<T>::sc_allocate(){

    if(free_slabs_st.empty()){

        vectorOfSlabs.push_back(new Slab<T>(10));
        free_slabs_st.push(vectorOfSlabs.back());
    }

    Slab<T>* slab = free_slabs_st.top();
    T* obj = slab->sb_allocate();

    if(slab->getStatus() == StatusOfSlotsAvailable::FULL) free_slabs_st.pop();

    return obj;
}

template <typename T>
void SlabCache<T>::sc_deallocate(T* ptr){
    for(auto& slab : vectorOfSlabs){
        if(slab->contains(ptr)){
            slab->sb_deallocate(ptr);

            if (slab->getStatus() != StatusOfSlotsAvailable::FULL) free_slabs_st.push(slab);
            
            return;
        }
    }
}