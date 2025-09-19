#pragma once
#include<iostream>
#include<stack>
#include "./MemoryManager.hpp"

enum class StatusOfSlotsAvailable{
    EMPTY,
    PARTIAL,
    FULL
};

template <typename T>
class Slab{

    private:
        T* memoryArray;
        StatusOfSlotsAvailable status;
        std::stack<T*> st;
        T* pointer;
        size_t slabsize;
        size_t usedSlots;
        MemoryManage* cache_passed_manager;
    public:
        explicit Slab(size_t c_slabsize, MemoryManage* c_MemoryManager);
        ~Slab();

        T* sb_allocate();
        void sb_deallocate(T* ptr);
        bool contains(T* ptr);
        StatusOfSlotsAvailable getStatus();
};

template <typename T> Slab<T>::Slab(size_t c_slabsize,MemoryManage* c_MemoryManager): slabsize(c_slabsize), usedSlots(0), status(StatusOfSlotsAvailable::EMPTY), cache_passed_manager(c_MemoryManager){
    memoryArray = static_cast<T*>(ud_malloc(sizeof(T) * slabsize));
    pointer = memoryArray;
}

template <typename T> Slab<T>::~Slab(){

    ud_free(memoryArray);
}

template <typename T> T* Slab<T>::sb_allocate(){
    if(status != StatusOfSlotsAvailable::FULL){ 
        T* newObj;
        if(st.empty()){
            if(pointer >= memoryArray+slabsize){
                return nullptr;
            }

            newObj = new(pointer) T();
            pointer++;
        }
        else{
            T* addressInStack = st.top();
            st.pop();
            newObj = new (addressInStack) T();
        }

        usedSlots++;

        status = usedSlots == slabsize ? StatusOfSlotsAvailable::FULL : StatusOfSlotsAvailable::PARTIAL;

        cache_passed_manager->AddMemory(newObj,sizeof(T));

        std::cout << "Allocated the memory" << std::endl;
        return newObj;
    }
    return nullptr;
}

template <typename T> void Slab<T>::sb_deallocate(T* ptr){
    int index = ptr-memoryArray;
    if(index >= 0 && index < slabsize){
        ptr->~T(); 

        st.push(ptr);
        usedSlots--;

        status = usedSlots == 0 ? StatusOfSlotsAvailable::EMPTY : StatusOfSlotsAvailable::PARTIAL;

        cache_passed_manager->removeMemory(ptr);

        std::cout << "Deallocated the memory successfully" << std::endl;
        return;
    }
    std::cout << "Error in deallocating" << std::endl;
}

template <typename T> bool Slab<T>::contains(T* ptr){
    int index = ptr-memoryArray;
    return index >= 0 && index < slabsize;
}

template <typename T> StatusOfSlotsAvailable Slab<T>::getStatus() {
    return status;
}

