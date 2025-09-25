#pragma once
#include <stddef.h>
#include <stdbool.h>
#include<stdlib.h>

#define STACK_CAPACITY 10

typedef struct {
    void* items[STACK_CAPACITY];
    int top;
} PointerStack;

PointerStack* StackInit();
bool StackPush(PointerStack* stack, void* item);
void* StackPop(PointerStack* stack);
bool StackIsEmpty(PointerStack* stack);
bool StackIsFull(PointerStack* stack);