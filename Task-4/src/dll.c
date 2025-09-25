
#include "./headers/dll.h"

DLL* DLL_Init(Slab* slab){
    DLL* returnPtr = (DLL*)malloc(sizeof(DLL));

    if(returnPtr == NULL) return NULL;
    
    returnPtr->slabInDLL = slab;
    returnPtr->next = NULL;
    returnPtr->prev = NULL; 

    return returnPtr;
}

void DLL_Destroy(DLL* dll_to_destroy){
    if(dll_to_destroy == NULL) return;
    free(dll_to_destroy);
}

void DLL_DestroyAll(DLL* head_ptr){

    DLL* current = head_ptr;
    while(current != NULL){
        DLL* nextOne = current->next;

        DLL_Destroy(current);
        current = nextOne;
    }

}

DLL* DLL_InsertAtEnd(DLL* tail, Slab* slabToAdd) {
    if (tail == NULL) return NULL;

    DLL* newOne = DLL_Init(slabToAdd);
    if (newOne == NULL) return tail;

    tail->next = newOne;
    newOne->prev = tail;
    return newOne; // Return new tail and update in call like -- tail = insertAtEnd(tail, slabToAdd);
}

void DLL_print(DLL* head_ptr) {
    DLL* current = head_ptr;
    while (current != NULL) {
        printf("%p \n", (void*)current); 
        current = current->next;
    }
}