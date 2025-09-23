#pragma once
#include<vector>
#include<stack>
#include <mutex>
#include"Slab.hpp"

template <typename T>
class SlabCache{
    private:
        std::vector<Slab<T>*> vectorOfSlabs;
        std::stack<Slab<T>*> free_slabs_st;
        MemoryManage cache_level_memory_manager;
        std::mutex cacheMutex;

    public:
        T* sc_allocate();
        void sc_deallocate(T* ptr);
        size_t getCacheLevelMemoryUsage();
};

template <typename T>
T* SlabCache<T>::sc_allocate(){
    std::lock_guard<std::mutex> lock(cacheMutex);
        if(free_slabs_st.empty()){
            vectorOfSlabs.push_back(new Slab<T>(10,&cache_level_memory_manager));
            free_slabs_st.push(vectorOfSlabs.back());
        }

        Slab<T>* slab = free_slabs_st.top();
        T* obj = slab->sb_allocate();

        if(slab->getStatus() == StatusOfSlotsAvailable::FULL) {
            free_slabs_st.pop();
        }
        return obj;
}

template <typename T>
void SlabCache<T>::sc_deallocate(T* ptr){
    std::lock_guard<std::mutex> lock(cacheMutex);
        for(auto& slab : vectorOfSlabs){
            if(slab->contains(ptr)){

                bool wasFull = (slab->getStatus() == StatusOfSlotsAvailable::FULL);
                slab->sb_deallocate(ptr);

                if(wasFull){
                    free_slabs_st.push(slab);
                }            
                return;
            }
        }
}

template <typename T>
size_t SlabCache<T>::getCacheLevelMemoryUsage(){
    std::lock_guard<std::mutex> lock(cacheMutex);
        return cache_level_memory_manager.getMemoryUsed();
}