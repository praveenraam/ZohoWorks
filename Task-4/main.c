#include "./src/headers/slab.h"
#include "./src/headers/pointerstack.h"

#include <stdio.h>

int main(){

    PointerStack* stack = StackInit();
    printf("%d ",StackIsEmpty(stack));
    printf("%d ",StackIsFull(stack));
    int no = 10;
    void* newPtr = &no;
    StackPush(stack,newPtr);
    printf("%d ",StackIsEmpty(stack));
    StackPop(stack);
    printf("%d ",StackIsEmpty(stack));

    for(int iter=0;iter<10;iter++){
        StackPush(stack,newPtr);
    }
    printf("%d ",StackIsFull(stack));

    for(int iter=0;iter<10;iter++){
        StackPop(stack);
    }
    printf("%d ",StackIsFull(stack));

}