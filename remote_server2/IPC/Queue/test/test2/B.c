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
        mq_receive(id_q, mess, sizeof(data), NULL);
        printf("%s %d %lf\n", mess->data_char, mess->data_i, mess->data_d);
    }
}

int main()
{
    data message;

    struct mq_attr attr;
    attr.mq_maxmsg = 5;
    attr.mq_msgsize = sizeof (data);
    id_q = mq_open(PATHNAME, O_RDWR | O_CREAT, MQ_MODE, &attr);

    if (id_q == -1)
    {
        printf("Can not create queue\n");
        return -1;
    }

    mq_getattr(id_q, &attr);
    printf("Number of mess: %ld\n", attr.mq_maxmsg);
    printf("Sizeof a mess : %ld\n", attr.mq_msgsize);

    if (pthread_create(&tid, NULL, &func, &message))
    {
        printf("Can not create thread error\n");
        return -1;
    }

    while(1);

    return 0;

}