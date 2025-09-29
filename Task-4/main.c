#include "./src/headers/slaballocator.h"
#include "./src/headers/dll.h"

#include <stdio.h>

void* testFunc(void* args){

    int count = 8;
    int removeCount = 2;
    int againAlloc = 2;

    void* ptrs[8];

    for(int iter=0;iter<count;iter++){
        ptrs[iter] = SA_Allocater(10);
        printf("Allocated : %p\n",ptrs[iter]);
    }

    for(int iter=0;iter<removeCount;iter++){
        SA_Deallocater(10,ptrs[iter]);
        printf("De Allocated : %p\n",ptrs[iter]);
    }

    for(int iter=0;iter<againAlloc;iter++){
        ptrs[iter] = SA_Allocater(10);
        printf("Again Allocated : %p\n",ptrs[iter]);
    }  

    return NULL;
}


int main() {
    
    pthread_t threads[4];

    for(int iter=0;iter<4;iter++){
        if(pthread_create(&threads[iter],NULL,testFunc,NULL) != 0){
            printf("Error");
            return 1;
        }
    }

    for(int iter=0;iter<4;iter++){
        pthread_join(threads[iter],NULL);
    }

}
