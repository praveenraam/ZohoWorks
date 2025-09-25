#pragma once
#include "./slab.h"
#include <stdio.h>

typedef struct DLL{
    Slab* slabInDLL;
    struct DLL* next;
    struct DLL* prev;
} DLL;

DLL* DLL_Init(Slab* slab);
void DLL_Destroy(DLL* dll_to_destroy);
void DLL_DestroyAll(DLL* head_ptr);
DLL* DLL_InsertAtEnd(DLL* tail, Slab* slabToAdd);
void DLL_print(DLL* head_ptr);