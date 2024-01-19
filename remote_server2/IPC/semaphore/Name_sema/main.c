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
int value;
pthread_t id1, id2;
sem_t *sema;

static void *func1(void *para) {
    printf("Thread 1 \n");
    while (1) {
        printf("Value of count : %d\n", count);
        if (count % 5 == 0) {
            if (sem_post(sema) == -1) {
                perror("sem_post");
                exit(EXIT_FAILURE);
            }
        }

        count++;
        sleep(1);
    }
}

static void *func2(void *para) {
    printf("Thread 2\n");
    while (1) {
        if (sem_wait(sema) == -1) {
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }
        printf("Count reach check value\n");
    }
}

int main() {
    sema = sem_open("/test_sema", O_CREAT , 0666, 0);

    if (sema == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    sem_getvalue(sema, &value);
    printf("initial value of semaphore is : %d\n", value);

    pthread_create(&id1, NULL, &func1, NULL);
    pthread_create(&id2, NULL, &func2, NULL);

    while (1) {
        // Your main program logic here
    }

    sem_close(sema);

    if (sem_unlink("/test_sema") == -1) {
        perror("sem_unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}
