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

        SlabCache& getCache();
        std::unordered_map<std::string, void*> cacheMap;

    public :
        static SlabAllocator* getInstance();
        void printMap();

        MyClass* allocate(std::string name);
        void deallocate(MyClass* ptr);
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


MyClass* SlabAllocator::allocate(std::string name){
    auto& cacheObj = getCache();
    return cacheObj.sl_allocate(name); 
}

void SlabAllocator::deallocate(MyClass* ptr){
    auto& cacheObj = getCache();
    cacheObj.deallocate(ptr);
}

SlabCache& SlabAllocator::getCache(){

    // std::string typeName = typeid(T).name();

    std::string typeName = "MyClass";
    if (cacheMap.find(typeName) == cacheMap.end()){
        cacheMap[typeName] = new SlabCache();
    }
    return *static_cast<SlabCache*>(cacheMap[typeName]);
}
