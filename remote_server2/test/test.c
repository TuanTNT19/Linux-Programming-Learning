#include <stdio.h>
#include <string.h>
#include <mqueue.h>  
#include <errno.h>  

#define MQ_MODE (S_IRUSR | S_IWUSR ) 


typedef struct{
    long priority;
    char str[50];
}data;

int main()
{
   
    data test1 , test2;
    int r , s;

    struct mq_attr attr;
    //set max message and max size of a message
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    
    mqd_t mqid = mq_open("/mqueue", O_RDWR | O_CREAT | O_NONBLOCK , MQ_MODE, &attr);  //open queue
      if (mqid == -1) {  
        printf("mq_open() error %d: %s\n", errno, strerror(errno));  
        return -2;  
    } 

    printf("Data 1:\n");
    scanf("%ld",&test1.priority);
    getchar();
    fgets(test1.str, 50, stdin);
    s = mq_send(mqid, &test1, sizeof(test1), NULL);
    if (s == -1)
    {
        printf("Can not send 1\n");
    }

    printf("Data 2:\n");
    scanf("%ld",&test1.priority);
    getchar();
    fgets(test1.str, 50, stdin);
    s = mq_send(mqid, &test1, sizeof(test1), NULL);
    if (s == -1)
    {
        printf("Can not send 2\n");
    }


//menu 
    r = mq_receive(mqid, &test2, 100, NULL);   //receive and delete a infor in mqueue
    if ( r == -1)
    {
        printf("Can not receive \n");
    }
    printf("%ld %s\n",test2.priority, test2.str);

        r = mq_receive(mqid, &test2, 100, NULL);   //receive and delete a infor in mqueue
    if ( r == -1)
    {
        printf("Can not receive \n");
    }
    printf("%ld %s\n",test2.priority, test2.str);

    mq_close(mqid); //close queue id
    if (mq_unlink("/mqueue") == -1) //remove mqueue
    {
        printf("Can not delete Queue\n");
    }
    else{
        printf("Unlink OK\n");
    }
    return 0;
}