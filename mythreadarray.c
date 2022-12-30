#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
    int numThreads = 5;

    int arraySlice = ARRAY_SIZE / numThreads;
    if (arraySlice * numThreads < ARRAY_SIZE) {
        ++arraySlice;
    }

    // Declare sum dynamically to return to join:
    int* thread_sum = (int*) calloc(1, sizeof(int));
    
    //NOTE: uncomment the printf commands below to see behind the scenes
    if(n == 0){
        for(int i = 0; i < arraySlice; i++){
        	//printf("Working in thread %d, at position: %d\n", ptr->tid , i );
            thread_sum[0] = thread_sum[0] + ptr->arr[i];
        }
    }
    else if (n == 1)
    {
        for(int i = arraySlice; i < arraySlice*2; i++){
        	//printf("Working in thread %d, at position: %d\n", ptr->tid , i );
            thread_sum[0] = thread_sum[0] + ptr->arr[i];
        }
    }
    else if (n == 2)
    {
        for(int i = arraySlice*2; i < arraySlice*3; i++){
        	//printf("Working in thread %d, at position: %d\n", ptr->tid , i );
            thread_sum[0] = thread_sum[0] + ptr->arr[i];
        }
    }
    else if (n == 3)
    {
        for(int i = arraySlice*3; i < arraySlice*4; i++){
        	//printf("Working in thread %d, at position: %d\n", ptr->tid , i );
            thread_sum[0] = thread_sum[0] + ptr->arr[i];
        }
    }
    else{
        for(int i = arraySlice*4; i < ARRAY_SIZE; i++){
            //printf("Working in thread %d, at position: %d\n", ptr->tid , i );
            thread_sum[0] = thread_sum[0] + ptr->arr[i];
         }
    }
    
    pthread_exit(thread_sum);
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    // Declare integer array [1,2,3,4,5,6,7,8,9,10]:
    int* int_arr = (int*) calloc(ARRAY_SIZE, sizeof(int));
    for(int i = 0; i < ARRAY_SIZE; i++)
        int_arr[i] = (rand() % 100) + 1;
        //printf("%i\t",int_arr[i]);
        
    // Declare arguments for both threads:
    paramListType thread_params[5];
    thread_params[0].tid = 0;
    thread_params[0].arr = int_arr;
    thread_params[1].tid = 1;
    thread_params[1].arr = int_arr;
    thread_params[2].tid = 2;
    thread_params[2].arr = int_arr;
    thread_params[3].tid = 3;
    thread_params[3].arr = int_arr;
    thread_params[4].tid = 4;
    thread_params[4].arr = int_arr;
    
    // Declare thread IDs:
    pthread_t tids[5];
    
    // create threads:
    pthread_create(&tids[0], NULL, threadSum, &thread_params[0]);
    pthread_create(&tids[1], NULL, threadSum, &thread_params[1]);
    pthread_create(&tids[2], NULL, threadSum, &thread_params[2]);
    pthread_create(&tids[3], NULL, threadSum, &thread_params[3]);
    pthread_create(&tids[4], NULL, threadSum, &thread_params[4]);
    
    // declare sums:
    int* sum0;
    int* sum1;
    int* sum2;
    int* sum3;
    int* sum4;
    
    // retrieve sum of threads:
    pthread_join(tids[0], (void**)&sum0);
    pthread_join(tids[1], (void**)&sum1);
    pthread_join(tids[2], (void**)&sum2);
    pthread_join(tids[3], (void**)&sum3);
    pthread_join(tids[4], (void**)&sum4);
    
    printf("Sum of whole array = %i\n", *sum0 + *sum1 + *sum2 + *sum3 + *sum4);
    
    return 0;
}
