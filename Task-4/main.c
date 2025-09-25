#include "./src/headers/slab.h"
#include "./src/headers/dll.h"
#include<stdio.h>

int main(){

    Slab* s1 = SlabInit(2,10);
    Slab* s2 = SlabInit(1,10);
    Slab* s3 = SlabInit(3,7);
    Slab* s4 = SlabInit(4,10);

    DLL* header = DLL_Init(s1);
    DLL* Tail = header;
    Tail = DLL_InsertAtEnd(Tail,s2);
    Tail = DLL_InsertAtEnd(Tail,s3);
    Tail = DLL_InsertAtEnd(Tail,s4);
    
    DLL_print(header);
    
    Tail = Tail->prev;
    DLL* End = Tail->next;
    Tail->next = NULL;
    DLL_Destroy(End);

    DLL_print(header);

    DLL_DestroyAll(header);
    

}