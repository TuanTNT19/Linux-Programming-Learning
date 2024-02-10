#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>

#define SEMAPHORE_NAME "/sema_test_P"
sem_t *sema;
pthread_t id;

static void *f(void *para)
{
    int count = 1;
    while(1)
    {
        count ++;
        printf("Count : %d\n", count);
        if (count %6 == 0){
            sem_post(sema);
        }
        sleep(1);
    }
}

int main()
{
    sema = sem_open(SEMAPHORE_NAME, O_RDWR | O_CREAT, 0666, 0);
   
    if (pthread_create(&id, NULL, &f, NULL)==-1)
    {
        printf("CAn not create thread\n");
        return -1;
    }

    while(1);

    return 0;


   
}