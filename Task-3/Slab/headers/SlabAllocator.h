#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <typeinfo>
#include "SlabCache.h"

class SlabAllocator{
    private:
        SlabAllocator() = default;
        ~SlabAllocator() = default;

        template<typename T> SlabCache<T>& getCache();
        
        std::unordered_map<std::string, std::unique_ptr<void>> cacheMap;

    public :
        static SlabAllocator* getInstance();

        template<typename T> T* allocate();
        template<typename T> void deallocate(T* ptr);
};