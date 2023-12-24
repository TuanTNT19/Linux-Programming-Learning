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

int count = 1;
int value ;
pthread_t id1 , id2 ;
sem_t *sema;

static void *func1(void *para)
{
    printf("Thread 1 \n");
    while(1)
    {
        printf("Value of count : %d\n", count );
        if (count % 5 == 0)
        {
           sem_post(sema);
        }

        count ++;
        sleep(1);
    }
}

static void *func2(void *para)
{
    printf("Thread 2\n");
    while(1)
    {
        sem_wait(sema);
        printf("Count reach check value\n");
       // sleep(1);
    }
}

int main()
{
   // sem_t *sema;

    //sem_init(&sema, 0, 0);
    sema = sem_open("/test_sema", O_CREAT | O_EXCL, 0666, 0);
    sema = (sem_t *)malloc(sizeof(sem_t));

    sem_getvalue(sema, &value);
    printf("intitial value of semaphore is : %d\n ", value);
   // printf("Check \n");

    pthread_create(&id1, NULL, &func1, NULL);
    pthread_create(&id2, NULL, &func2, NULL);

    while(1);
    
   // sem_destroy(&sema);
     sem_close(sema);

     sem_unlink("./test_sema");

    return 0;
}