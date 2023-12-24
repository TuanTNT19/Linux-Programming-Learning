#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
pthread_t id1, id2;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER ;
int c = 2;//share resouces
static void *thr_handle1(void *args)
{
    pthread_mutex_lock(&m);
    c++;
    printf("Value of C in thread 1 : %d\n",c);
    sleep(1);
    pthread_mutex_unlock(&m);
}
static void *thr_handle2(void *args)
{
    pthread_mutex_lock(&m);
    c++;
    printf("Value of C in thread 2 : %d\n",c);
    //sleep(1);
    pthread_mutex_unlock(&m);
}
int main()
{
    int ret;

    if (ret = pthread_create(&id1,NULL,&thr_handle1,NULL))
    {
        printf("can not create thread 1 %d\n",ret);
        return -1;
    }
        if (ret = pthread_create(&id2,NULL,&thr_handle2,NULL))
    {
        printf("can not create thread 2 %d\n",ret);
        return -1;
    }

    while(1);

    return 0;
}