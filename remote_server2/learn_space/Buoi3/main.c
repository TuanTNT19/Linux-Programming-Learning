#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
pthread_t id1, id2;
typedef struct{
    char name[30];
    char msg[30];
}thr_data_t;
static void *thr_handle1(void *args)
{
   // pthread_t tid = pthread_self();
   // thr_data_t *data = (thr_data_t *)args;
    printf("I am thread 1\n");
    sleep(2);
    printf("thread 1 end \n");
    pthread_cancel(id2);
    
}
static void *thr_handle2(void *args)
{
    printf("I am thread Handle 2\n");
    sleep(5);
    printf("Thread 2 end \n");

}
int main()
{
    int ret;
    thr_data_t data ={0};
    strncpy(data.name, "TuanTNT19",sizeof(data.name));
    strncpy(data.msg, "Irene Bae Joo Huyn\n",sizeof(data.msg));
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