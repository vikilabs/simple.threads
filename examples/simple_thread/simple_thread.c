#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <unistd.h>

#define THREADS_COUNT 2

void *function_1(void *t_index) 
{ 
    long thread_index;
    int i;
    
    thread_index = *((long *) t_index);
    printf("[ child_thread %ld ] started\n", thread_index);
    
    for(i=1;i<=5;i++){
        printf("[ child_thread %ld ] sleeping %d\n", thread_index, i);
        sleep(1);
    }

    printf("[ child_thread %ld ] exitting\n", thread_index);

    pthread_exit(NULL);
}

void *function_2(void *t_index)
{
    long thread_index;
    int i;
    
    thread_index = *((long *) t_index);
    printf("[ child_thread %ld ] started\n", thread_index);
    
    for(i=1;i<=10;i++){
        printf("[ child_thread %ld ] sleeping %d\n", thread_index, i);
        sleep(1);
    }
    
    printf("[ child_thread %ld ] exitting\n", thread_index);
    
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
    long thread_index_1 = 1;
    long thread_index_2 = 2;
   
    printf("[ main_thread    ] creating child thread 1 to execute function_1() \n");
    ret = pthread_create(&threads[0], NULL, function_1, (void *) &thread_index_1); 
    check_status(ret);    
    

    printf("[ main_thread    ] creating child thread 2 to execute function_2() \n");
    ret = pthread_create(&threads[1], NULL, function_2, (void *) &thread_index_2);
    check_status(ret);    
    
 
    /* Wait for all threads to complete their jobs */ 
    for (i = 0; i < THREADS_COUNT; i++) {
        pthread_join(threads[i], NULL); 
    }
   
    /* Exit Main Thread*/
    printf("[ main_thread    ] exitting\n");
    pthread_exit(NULL); 

}
