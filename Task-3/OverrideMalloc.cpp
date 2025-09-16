#include "OverrideMalloc.h"

    // Obj returner
MemoryManage* MemoryManage::getMemoryManageObj(){
    if(obj == nullptr) obj = new MemoryManage();
    return obj; 
}

    // Add values to memory
void MemoryManage::AddMemory(void* ptr,int size){
    memoryUsedByProgram+=size;
    mapForSize.insert({ptr,size});
}

    // Remove values to memory
void MemoryManage::removeMemory(void* ptr){
    auto iter = mapForSize.find(ptr);
    if(iter != mapForSize.end()){
        memoryUsedByProgram = memoryUsedByProgram - (iter->second);
        mapForSize.erase(iter);
    }
    else std::cout << "ptr in param is not found" << std::endl;

}

    // getter for MemoryUsed
size_t MemoryManage::getMemoryUsed(){
    return memoryUsedByProgram;
}

    // static variable declaration
MemoryManage* MemoryManage::obj = nullptr;


// User defined malloc
void* ud_malloc(std::size_t size){
    
    std::cout << "We are doing our work and then calling" << std::endl;
    std::cout << "Size : " << size << std::endl;
    
    void* address = malloc(size);

    if(address == nullptr){
        return nullptr;
    }

    MemoryManage* memoryManage = MemoryManage::getMemoryManageObj();
    memoryManage->AddMemory(address,size);

    return address;
}

// User defined free
void ud_free(void* ptr){
    std::cout << "we are doing our work and then calling default function" << std::endl;
    
    MemoryManage* memoryManage = MemoryManage::getMemoryManageObj();
    memoryManage->removeMemory(ptr);
    
    free(ptr);
}


// void* malloc(size_t size){    
// }

// void* operator new(std::size_t size){
//     std::cout << "We are calling ud new" << std::endl;

//     if(size == 0 ) ++size;

//     if(void* ptr = ud_malloc(size)){
//         return ptr;
//     }

//     throw std::bad_alloc{};
// }

// void* operator new[](std::size_t size){
//     std::cout << "We are calling ud new[]" << std::endl;

//     if(size == 0) ++size;

//     if(void* ptr = ud_malloc(size)){
//         return ptr;
//     }

//     throw std::bad_alloc{};
// }

// void operator delete(void* ptr) noexcept { // Check what is this line -- no exxcept
//     std::cout << "we are removing" << std::endl;
//     free(ptr);
// } 

// void operator delete[](void* ptr) noexcept { // Check what is this line -- no exxcept
//     std::cout << "we are removing []" << std::endl;
//     free(ptr);
// }

int main(){
    int* arr = (int*)ud_malloc(4*sizeof(int));

    for(int iter=0;iter<4;iter++){
        std::cout << arr[iter] << std::endl;
    }

    for(int iter=0;iter<4;iter++){
        arr[iter] = iter*iter;
    }

    for(int iter=0;iter<4;iter++){
        std::cout << arr[iter] << std::endl;
    }

    MemoryManage* memoryManage = MemoryManage::getMemoryManageObj();
    std::cout << "Used Memory from Memory Manage : " << memoryManage->getMemoryUsed() << std::endl;

    ud_free(arr);

    std::cout << "Used Memory from Memory Manage : " << memoryManage->getMemoryUsed() << std::endl;

    for(int iter=0;iter<4;iter++){
        std::cout << arr[iter] << std::endl;
    }
}