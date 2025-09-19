#pragma once
#include<iostream>
#include<stack>

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
    pointer = memoryArray;
}

template <typename T> Slab<T>::~Slab(){

    

    std::free(memoryArray);
}

template <typename T> T* Slab<T>::sb_allocate(){
    if(status != StatusOfSlotsAvailable::FULL){ 
        T* newObj;
        if(st.empty()){
            std::cout << "empty\n";
            if(pointer >= memoryArray+slabsize){
                return nullptr;
            }

            newObj = new(pointer) T();
            pointer++;
        }
        else{
            std::cout << "Not empty\n";
            T* addressInStack = st.top();
            st.pop();
            newObj = new (addressInStack) T();
        }

        usedSlots++;

        status = usedSlots == slabsize ? StatusOfSlotsAvailable::FULL : StatusOfSlotsAvailable::PARTIAL;

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

