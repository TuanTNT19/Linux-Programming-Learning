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
static void *thr_handle(void *args)
{
    pthread_t tid = pthread_self();
    thr_data_t *data = (thr_data_t *)args;
    if (pthread_equal(tid,id1))
    {
        printf("In am thread 1 \n");
    }
    else{
        printf(" I am thread 2\n");
        printf("Hello %s %s\n",data->name, data->msg);
    }
}
static void *thr_handle2(void *args)
{
    printf("I am thread Handle 2\n");

}
int main()
{
    int ret;
    thr_data_t data ={0};
    strncpy(data.name, "TuanTNT19",sizeof(data.name));
    strncpy(data.msg, "Irene Bae Joo Huyn\n",sizeof(data.msg));
    if (ret = pthread_create(&id1,NULL,&thr_handle,NULL))
    {
        printf("can not create thread 1 %d\n",ret);
        return -1;
    }
    sleep(2);
        if (ret = pthread_create(&id2,NULL,&thr_handle,&data))
    {
        printf("can not create thread 2 %d\n",ret);
        return -1;
    }
    sleep(5);
    return 0;
}