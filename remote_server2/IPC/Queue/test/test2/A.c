#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <mqueue.h>
#include <pthread.h>


#define PATHNAME "/queuetest"
#define MQ_MODE (S_IRUSR | S_IWUSR ) 
mqd_t id_q;
pthread_t tid;

typedef struct {
    char data_char[20];
    int data_i;
    double data_d;
}data;


static void *func(void *para)
{
    data *mess = (data *)para;
    //mess->data_i = 1;

    while(1)
    {
        mess->data_i ++;
        
      printf("Value of i : %d\n", mess->data_i);
        if ((mess->data_i) % 6 == 0)
        {
            strcpy(mess->data_char, "Tuan TNT");
            mess->data_d = 21.6;
            mq_send(id_q, mess, sizeof(data), NULL);
        }
        sleep(1);
    }
}

int main()
{
    data message;
    message.data_i = 1;

    struct mq_attr attr, attR_check;
    attr.mq_maxmsg = 5;
    attr.mq_msgsize = sizeof (data);
    
    id_q = mq_open(PATHNAME, O_RDWR | O_CREAT, MQ_MODE, &attr);

    if (id_q == -1)
    {
        printf("Can not create queue\n");
        return -1;
    }

    mq_getattr(id_q, &attR_check);
    printf("Number of mess: %ld\n", attR_check.mq_maxmsg);
    printf("Sizeof a mess : %ld\n", attR_check.mq_msgsize);

    if (pthread_create(&tid, NULL, &func, &message))
    {
        printf("Can not create thread error\n");
        return -1;
    }

    while(1);

    return 0;

}