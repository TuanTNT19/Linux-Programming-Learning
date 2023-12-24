#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <mqueue.h>

#define pathname "queuex"
#define MQ_MODE (S_IRUSR | S_IWUSR ) 
int main()
{
    mqd_t id ;
    struct mq_attr attr;
    id = mq_open("/queuex", O_RDWR | O_CREAT | O_NONBLOCK, MQ_MODE , NULL);

    if (id == -1)
    {
        printf("Can not make queue\n");
        return 0;
    }

    mq_getattr(id,&attr);
    printf("Number of mess: %ld\n",attr.mq_maxmsg);
    printf("sizeof a mess: %ld\n",attr.mq_msgsize);
    printf("Currnent of mess : %ld\n",attr.mq_curmsgs);

    mq_close(id);
    mq_unlink(pathname);
    return 0;


}