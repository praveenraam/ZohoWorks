#include "./src/headers/slab.h"

#include <stdio.h>

int main(){

    Slab* slab = SlabCreate(10,10);
    printf("We have created a slab that contains a memory array of size : %ld\n",  slab->totalMemorySizeOfArray);
    printf("%d\n",getStatus(slab));
    SlabDestroy(slab);
}