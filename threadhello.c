#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUMBER_OF_THREADS 10

/* This is a structure that is used to pass parameters to the thread.
 * Currently, the only param is the thread id */
typedef struct
{
    int tid;
} paramListType;

/* *params should be pointing to a structure of paramListType */ 
void *print_hello_world(void *params)
{
    paramListType *paramPtr = params;

    printf("Hello World. Greetings from thread %d\n", paramPtr->tid) ;
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i;
    
    /* parms will be a pointer to a parmListType structure that will
     * contain the thread id value */
    paramListType *params;
    
    for(i=0; i<NUMBER_OF_THREADS; i++)
    {
        printf("Main here. Creating thread %d\n", i);
        
        /* dynamically create a structure to hold the parameter list */
        params = (paramListType *)malloc( sizeof(paramListType));
        params->tid = i;
        
        status = pthread_create(&threads[i], NULL, print_hello_world, (void *) params);
        
        if(status != 0)
        {
            printf("pthread_create returned error code %d\n", status);
            exit(-1);
        }
    }
    
    /* if the program doesn't wait for all the threads to finish, 
     * you may not see the print message from some of them */
    for(i=0; i<NUMBER_OF_THREADS; i++)
    {
        status=pthread_join(threads[i], NULL);
    }
    exit(0);
}
