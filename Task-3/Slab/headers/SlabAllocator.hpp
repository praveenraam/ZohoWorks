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

        SlabCache<HerClass>& getCache();
        std::unordered_map<std::string, void*> cacheMap;

    public :
        static SlabAllocator* getInstance();
        void printMap();

        HerClass* allocate(std::string name);
        void deallocate(HerClass* ptr);
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


HerClass* SlabAllocator::allocate(std::string name){
    auto& cacheObj = getCache();
    return cacheObj.sl_allocate(); 
}

void SlabAllocator::deallocate(HerClass* ptr){
    auto& cacheObj = getCache();
    cacheObj.deallocate(ptr);
}

SlabCache<HerClass>& SlabAllocator::getCache(){

    // std::string typeName = typeid(T).name();

    std::string typeName = "HerClass";
    if (cacheMap.find(typeName) == cacheMap.end()){
        cacheMap[typeName] = new SlabCache<HerClass>();
    }
    return *static_cast<SlabCache<HerClass>*>(cacheMap[typeName]);
}
