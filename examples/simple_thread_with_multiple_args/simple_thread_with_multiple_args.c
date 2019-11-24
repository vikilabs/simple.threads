#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <unistd.h>

#define THREADS_COUNT 2

typedef struct{
    int thread_index;
    int sleep_count;
}thread_1_arguments_t;

typedef struct{
    int thread_index;
    int sleep_count;
}thread_2_arguments_t;

void *function_1(void *args) 
{ 
    int i;
    
    thread_1_arguments_t *targs = (thread_1_arguments_t *) args;

    printf("[ child_thread %d ] started\n", targs->thread_index);
    
    for(i=1; i<=targs->sleep_count; i++){
        printf("[ child_thread %d ] sleeping %d\n", targs->thread_index, i);
        sleep(1);
    }

    printf("[ child_thread %d ] exitting\n", targs->thread_index);

    pthread_exit(NULL);
}

void *function_2(void *args) 
{ 
    int i;
    
    thread_1_arguments_t *targs = (thread_1_arguments_t *) args;

    printf("[ child_thread %d ] started\n", targs->thread_index);
    
    for(i=1; i<=targs->sleep_count; i++){
        printf("[ child_thread %d ] sleeping %d\n", targs->thread_index, i);
        sleep(1);
    }

    printf("[ child_thread %d ] exitting\n", targs->thread_index);

    pthread_exit(NULL);
}

void check_status(int ret)
{
    if(ret){
        printf("[ main_thread    ]  error, unable to create child thread ( %d )\n", ret);
        exit(-1);
    }
}

int main (int argc, char *argv[]) 
{
    printf("[ main_thread    ] started\n");
    pthread_t threads[THREADS_COUNT]; /* Create 4 Thread Variables */ 
    int ret;
    long i;
    thread_1_arguments_t t1_args;
    thread_2_arguments_t t2_args;
    t1_args.thread_index = 1;
    t1_args.sleep_count = 5;
    t2_args.thread_index = 2;
    t2_args.sleep_count = 10;
   
    printf("[ main_thread    ] creating child thread 1 to execute function_1() \n");
    ret = pthread_create(&threads[0], NULL, function_1, (void *) &t1_args); 
    check_status(ret);    
    

    printf("[ main_thread    ] creating child thread 2 to execute function_2() \n");
    ret = pthread_create(&threads[1], NULL, function_2, (void *) &t2_args);
    check_status(ret);    
    
 
    /* Wait for all threads to complete their jobs */ 
    for (i = 0; i < THREADS_COUNT; i++) {
        pthread_join(threads[i], NULL); 
    }
   
    /* Exit Main Thread*/
    printf("[ main_thread    ] exitting\n");
    pthread_exit(NULL); 

}
