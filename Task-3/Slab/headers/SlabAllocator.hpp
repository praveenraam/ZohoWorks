#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <typeinfo>
#include <iostream>
#include <any>
#include "SlabCache.hpp"

class SlabAllocator{
    private:
        SlabAllocator() = default;
        ~SlabAllocator() = default;

        template<typename T> SlabCache<T>& getCache();
        std::unordered_map<std::string, void*> cacheMap;

    public :
        static SlabAllocator* getInstance();
        void printMap();

        template<typename T> T* sa_allocate();
        
        template<typename T> void sa_deallocate(T* ptr);
};


SlabAllocator* SlabAllocator::getInstance()
{
    static SlabAllocator instance;
    return &instance;
}

inline void SlabAllocator::printMap()
{
    for (const auto& it : cacheMap) {
        std::cout << "Key: " << it.first << " " << it.second << std::endl;
    }
}


template<typename T> T* SlabAllocator::sa_allocate(){
    auto& cacheObj = getCache<T>();
    return cacheObj.sc_allocate(); 
}

template<typename T> void SlabAllocator::sa_deallocate(T* ptr){
    auto& cacheObj = getCache<T>();
    cacheObj.sc_deallocate(ptr);
}

template<typename T> SlabCache<T>& SlabAllocator::getCache(){

    std::string typeName = typeid(T).name();

    // std::string typeName = "HerClass";
    if (cacheMap.find(typeName) == cacheMap.end()){
        cacheMap[typeName] = new SlabCache<T>();
    }
    return *static_cast<SlabCache<T>*>(cacheMap[typeName]);
}
