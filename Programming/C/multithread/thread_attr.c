#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define NUM 5

void * wait_n(void *t)
{
    int i;
    long tid;
    tid=(long)t;
    sleep(1);
    printf("Sleeping in thread...\n");
    printf("thread with id: %ld ...exit\n", tid);
    pthread_exit(NULL);
}

int main()
{
    int rc;
    int i;
    pthread_t threads[NUM];
    void *status;
    pthread_attr_t attr;
    //void * status;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    for(i=0; i<NUM; ++i)
    {
        printf("main(): creating thread, %d\n",i);
/*
first argument for pthread_create is the identifier of the thread, second is the thread attribute, third is the entry of the function, fourth is the argument for the function passed in. 
*/
        rc=pthread_create(&threads[i], NULL, wait_n, (void *)&i);
        if(rc)
        {
            printf("Error:unable to create thread,%d\n",rc);
            exit(-1);
        }
    }
    pthread_attr_destroy(&attr);
    for(i=0;i<NUM;++i)
    {
        rc=pthread_join(threads[i],&status);
        if(rc)
        {
            printf("ERROR: unable to join, %d\n",rc);
            exit(-1);
        }
        printf("main:completed thread id: %d\n",i);
        printf(" exit with status: %d\n",*(int *)(status));
    }
    printf("main: program exiting.\n");
    pthread_exit(NULL);
    return 0;
}