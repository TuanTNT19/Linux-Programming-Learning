#include <stdio.h>
#include <string.h>
#include <mqueue.h>  
#include <errno.h>  
#include <pthread.h>

#define MQ_MODE (S_IRUSR | S_IWUSR ) 

mqd_t mqid;
pthread_t thr_id;

typedef struct{
    char data_char[20];
    int data_i;
    double data_d;
}data;

static void *func(void *para)
{
    data *mess_re = (data *)para;
    printf("Program 2: \n");

    while(1)
    {
        mq_receive(mqid, (char *)mess_re, sizeof(data), NULL);
        printf("%s %lf %d\n", mess_re->data_char, mess_re->data_d, mess_re->data_i);

    }

}

int main()
{
    data message ={0};

    struct mq_attr attr;
    attr.mq_maxmsg = 5;
    attr.mq_msgsize = sizeof(data);
 //   printf("After\n");
    mqid = mq_open("/t_queue",O_RDWR | O_CREAT,MQ_MODE, &attr);
    if (mqid == -1)
    {
        printf("Can not create queue\n");
        return -1;

    }
 //   printf("Before\n");

    if (pthread_create(&thr_id, NULL, &func, &message)==-1)
    {
        printf("Can not create thread\n");
        return -1;
    }

    while(1);

    return 0;
}