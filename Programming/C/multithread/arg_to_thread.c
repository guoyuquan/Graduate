#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM 5

struct thread_data
{
    int thread_id;
    char *message;
};

void * PrintHello(void *threadarg)
{
    struct thread_data *my_data;
    my_data=(struct thread_data *) threadarg;
    printf("thread ID: %i\n", my_data->thread_id);
    printf("Message: %s \n",my_data->message);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM];
    struct thread_data td[NUM];
    int rc;
    int i;
    
    for(i=0;i<NUM;++i)
    {
        printf("main(): create thread, %d\n", i);
        td[i].thread_id=i;
        td[i].message="this is message";
        rc=pthread_create(&threads[i],NULL, PrintHello,(void*)&td[i]);
        if(rc)
        {
            printf("Error: unable to create thread,%d",rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
    return 0;
}