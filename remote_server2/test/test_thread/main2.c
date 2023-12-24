#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

pthread_t id1,id2,id3;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER ;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cont = PTHREAD_COND_INITIALIZER;
int i = 1;
int j = 0;
static void *func1(void *para)
{
    while(1){
        pthread_mutex_lock(&m);
        if(i != 1)
        {
            pthread_cond_wait(&cont, &m);
        }
        char *s = (char *)para;
        printf("Nhap str: ");
        fgets(s, 40, stdin);
        
        i = 0;
        j = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&m);


    }
}

static void *func2 ( void *para)
{
    while(1){
        pthread_mutex_lock(&m);

        char *s = (char *)para;
        if(j != 1)
        {
            pthread_cond_wait(&cond, &m);
        }
        
        j = 0;
        i = 1;
        pthread_cond_signal(&cont);
        printf("Str ms nhap la: %s\n",s);
        pthread_mutex_unlock(&m);
    }
}

static void *func3(void *para)
{
    while(1)
    {
        printf("Checking ........................\n");
        sleep(2);
    }
}

int main()
{
    char str[50];

    if (pthread_create(&id1,NULL,&func1,&str)){
        printf("Create Thread 1 Error\n");
    }

    if (pthread_create(&id2,NULL,&func2,&str)){
        printf("Create Thread 1 Error\n");
    }

    if (pthread_create(&id3,NULL,&func3,NULL)){
        printf("Create Thread 1 Error\n");
    }
    
    while(1);

    return 0;

}