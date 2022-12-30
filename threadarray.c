#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define ARRAY_SIZE 15

/* This is a structure that is used to pass parameters to the thread.
 * Currently, the only param is the thread id */
typedef struct
{
    int* arr;
    int tid;
} paramListType;

void* threadSum(void* p){
    paramListType* ptr = (paramListType*)p;
    int n = ptr->tid;
    
    // Declare sum dynamically to return to join:
    int* thread_sum = (int*) calloc(1, sizeof(int));
    
    //NOTE: uncomment the printf commands below to see behind the scenes
    if(n == 0){
        for(int i = 0; i < ARRAY_SIZE/2; i++){
        	  //printf("Working in thread %d, at position: %d\n", ptr->tid , i );
            thread_sum[0] = thread_sum[0] + ptr->arr[i];
        }
    }
    else{
        for(int i = ARRAY_SIZE/2; i < ARRAY_SIZE; i++){
            //printf("Working in thread %d, at position: %d\n", ptr->tid , i );
            thread_sum[0] = thread_sum[0] + ptr->arr[i];
         }
    }
    
    pthread_exit(thread_sum);
}

int main(int argc, char **argv)
{
    // Declare integer array [1,2,3,4,5,6,7,8,9,10]:
    int* int_arr = (int*) calloc(ARRAY_SIZE, sizeof(int));
    for(int i = 0; i < ARRAY_SIZE; i++)
        int_arr[i] = i + 1;
        
    // Declare arguments for both threads:
    paramListType thread_params[2];
    thread_params[0].tid = 0;
    thread_params[0].arr = int_arr;
    thread_params[1].tid = 1;
    thread_params[1].arr = int_arr;
    
    // Declare thread IDs:
    pthread_t tids[2];
    
    // create threads:
    pthread_create(&tids[0], NULL, threadSum, &thread_params[0]);
    pthread_create(&tids[1], NULL, threadSum, &thread_params[1]);
    
    // declare sums:
    int* sum0;
    int* sum1;
    
    // retrieve sum of threads:
    pthread_join(tids[0], (void**)&sum0);
    pthread_join(tids[1], (void**)&sum1);
    
    printf("Sum of whole array = %i\n", *sum0 + *sum1);
    
    return 0;
}
