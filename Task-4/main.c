#include "./src/headers/slab.h"
#include<stdio.h>

int main(){

    Slab* slab = SlabInit(10,10);
    printf("We have created a slab that contains a memory array of size : %ld\n",  slab->totalMemorySizeOfArray);
    void* ptr[10];

    for(int iter=0;iter<10;iter++){
        ptr[iter] = SlabAllocater(slab);
    }

    for(int iter=0;iter<10;iter++){
        printf("%p ",ptr[iter]);
    }
    
    SlabDeallocater(slab,ptr[2]);

    ptr[2] = SlabAllocater(slab);

    printf("Pointer 2 address %p\n",ptr[2]);

    void* dummy = SlabAllocater(slab);
    ptr[8]++;
    SlabDeallocater(slab,ptr[8]--);
    SlabDeallocater(slab,ptr[8]);
    SlabDeallocater(slab,ptr[10]);
    
    printf("is It contains ptr[7], %d\n",SlabContains(slab,ptr[7]));
    printf("is It contains dummy, %d\n",SlabContains(slab,dummy));
    printf("is It contains ptr[10], %d\n",SlabContains(slab,ptr[10]));

    printf("%d\n",getStatus(slab));
    SlabDestroy(slab);
}