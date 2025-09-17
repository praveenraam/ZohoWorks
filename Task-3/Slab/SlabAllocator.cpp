#include "headers/SlabAllocator.h"
// #include "headers/SlabAllocator.h"

SlabAllocator* SlabAllocator::getInstance()
{
    static SlabAllocator instance;
    return &instance;
}

template<typename T> T* SlabAllocator::allocate(){
    auto& cacheObj = getCache<T>();
    return cacheObj.template allocate<T>(); 
}

template<typename T> void SlabAllocator::deallocate(T* ptr){
    auto& cacheObj = getCache<T>();
    cacheObj.deallocate(ptr);
}

template<typename T> SlabCache<T>& SlabAllocator::getCache(){

    std::string typeName = typeid(T).name();
    if (cacheMap.find(typeName) == cacheMap.end()){
        cacheMap[typeName] = std::make_unique<SlabCache<T>>();
    }
    return *static_cast<SlabCache<T>*>(cacheMap[typeName].get());
}
