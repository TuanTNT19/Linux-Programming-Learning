#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <pthread.h>

#define SEMAPHORE_NAME "/sema_test"

sem_t *sema;
pthread_t id1, id2;
int count = 1;

static void *f1(void *para)
{
    while (1)
    {
        /* code */
        count++;
        printf("Count : %d\n", count);
        if (count % 6 == 0)
        {
            sem_post(&sema);
        }
        sleep(1);


    }
    
}

static void *f2(void *para)
{
    while (1)
    {
        sem_wait(&sema);
        printf("CHeck ok\n");

    }
}

int main()
{
    sema = (sem_t *)malloc(sizeof(sem_t)); // Allocate memory for sema

    if (sem_init(sema, 0, 0) == -1)
    {
        perror("Cannot create semaphore");
      //  free(sema); // Free the allocated memory
        return -1;
    }

    pthread_create(&id1, NULL, &f1, NULL);
    pthread_create(&id2, NULL, &f2, NULL);

    while (1);

    //free(sema); // Free the allocated memory
    return 0;
}
