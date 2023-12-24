
#include <stdio.h>
#include <string.h>
#include <mqueue.h>  
#include <errno.h>  

#define MQ_MODE (S_IRUSR | S_IWUSR ) 
char pathname[20] = "/myQueue" ;

char mess[50];
char messr[50];
int main()
{
    struct mq_attr attr;

    int id = mq_open(pathname, O_RDWR | O_CREAT, MQ_MODE, NULL);
    if (id == -1)
    {
        printf("Can not make queue\n");
        return 0;
    }
    

    int check;
    printf("Enter message from : ");
    fgets(mess, 50, stdin);

    check = mq_send(id, mess, sizeof(mess), 0);
    if (check == -1)
    {
        printf("Can not send message\n");
    }

    sleep(1);
    check = mq_receive(id, messr, sizeof(messr),(unsigned int *)NULL );
    if (check == -1)
    {
        printf("Can not send message\n");
    }
    printf("%s\n",messr)
    
    

    mq_close(id);

    mq_unlink(pathname);

    return 0;
}