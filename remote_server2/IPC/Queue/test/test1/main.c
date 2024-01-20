#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <mqueue.h>
#include <pthread.h>


#define PATHNAME "/queuetest"
#define MQ_MODE (S_IRUSR | S_IWUSR ) 
pthread_t id1,id2;

int check = 1;
mqd_t qid;

static void *func1(void *para)
{
    printf("Start thread 1\n");
    while(1)
    {
        check ++;
        printf("check from thread 1 : %d\n", check);
        if (check %5 == 0)
        {
            mq_send(qid, &check, sizeof(int), NULL);
        }
        sleep(1);
    }
}

static void *func2(void *para)
{
    int value ;
    printf("Start thread 2\n");
    while(1)
    {
        mq_receive(qid, &value, sizeof(value), NULL);
        printf("Checl from process 2: %d\n", value);

    }
}

int main()
{
    struct mq_attr attr, attr_check;

    attr.mq_maxmsg = 8;
    attr.mq_msgsize = sizeof(int);

    qid = mq_open(PATHNAME, O_RDWR | O_CREAT, MQ_MODE, &attr);
    if (qid == -1)
    {
        printf("Can not open queue\n");
        return -1;
    }

    mq_getattr(qid, &attr_check);
    printf("Number of mess: %ld\n", attr_check.mq_maxmsg);
    printf("sizeof a message: %ld\n", attr_check.mq_msgsize);
    
    
    // if (pthread_create(&id1,NULL,&func1,NULL)){
    //     printf("Create Thread 1 Error\n");
    //     return -1;
    // }
    
    // if (pthread_create(&id2,NULL,&func2,NULL)){
    //     printf("Create Thread 2 Error\n");
    //     return -1;
    // }

    sleep(20);

    return 0;


}