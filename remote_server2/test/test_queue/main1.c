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

static void *function(void *para)
{
    data *mess = (data *)para;

    while(1)
    {
        mess->data_i ++ ;
        printf("Data i : %d\n", mess->data_i);
        if ((mess->data_i % 6 == 0))
        {
            strcpy(mess->data_char, "Tuan TNT 6\n");
            mess->data_d = 10.5;
            mq_send(mqid, mess, sizeof(data), NULL);
            printf("Send ok 1\n");
            
        }

        if (((mess->data_i %6)==0) && ((mess->data_i)%4)==0)
        {
            strcpy(mess->data_char, "Tuan TNT12\n");
            mess->data_d = 10.12;
            mq_send(mqid, mess, sizeof(data), NULL);
            printf("Send ok 2\n");

        }
        sleep(1);
    }

}

int main()
{
    struct mq_attr attr;
    //mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
    
    mqid = mq_open("/t_queue",O_RDWR | O_CREAT,MQ_MODE, NULL );
    if (mqid == -1)
    {
        printf("Can not create queue\n");
        return -1;

    }

    data message;
    message.data_i = 1;

    if (pthread_create(&thr_id, NULL, &function, &message) == -1)
    {
        printf("Can not create thread\n");
        return -1;
    }

    while(1);

    return 0;
}