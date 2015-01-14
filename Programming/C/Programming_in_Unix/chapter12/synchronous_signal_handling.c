#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int quitflag;
sigset_t mask;

pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t wait1=PTHREAD_COND_INITIALIZER;

void * thr_fn(void * arg)
{
    int err, signo;
    for(;;)
    {
        err=sigwait(&mask, &signo);
        if(err!=0)
        {
            fprintf(stderr, "sigwait failed\n");
            exit(0);
        }
        switch(signo)
        {
            case SIGINT:
                printf("\ninterrupt\n");
                break;
            case SIGQUIT:
                pthread_mutex_lock(&lock);
                quitflag=1;
                pthread_mutex_unlock(&lock);
                pthread_cond_signal(&wait1);
                return (0);
            default:
                printf("unexpected signal %d\n", signo);
                exit(1);
        }
    }
}

int main()
{
    int err;
    sigset_t oldmask;
    pthread_t tid;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    if((err=pthread_sigmask(SIG_BLOCK, &mask, &oldmask))!=0)
    {
        fprintf(stderr, "SIG_BLOCK error\n");
        exit(0);
    }
    err=pthread_create(&tid, NULL, thr_fn, 0);
    if(err!=0)
    {
        fprintf(stderr, "can't create thread\n");
        exit(0);
    }
    pthread_mutex_lock(&lock);
    while(quitflag==0)
        pthread_cond_wait(&wait1, &lock);
    pthread_mutex_unlock(&lock);
    quitflag=0;
    if(sigprocmask(SIG_SETMASK, & oldmask, NULL)<0)
        printf("SIG_SETMASK error\n");
    exit(0);
}
