
#include <stdio.h>
#include <string.h>
#include <mqueue.h>  
#include <errno.h>  

#define MQ_MODE (S_IRUSR | S_IWUSR ) 
char pathname[20] = "/myQueue" ;

char mess[50];
int main()
{
    struct mq_attr attr;
    int check;
    int id = mq_open(pathname, O_RDWR | O_CREAT, MQ_MODE, NULL);
    if (id == -1)
    {
        printf("can not make queue\n");
        return 0;
    }
    
    check = mq_receive(id, mess, sizeof(mess),(unsigned int *)NULL );
    if (check == -1)
    {
        printf("Can not receive\n");
    }
    printf("%s\n",mess);

    mq_close(id);

    return 0;
}