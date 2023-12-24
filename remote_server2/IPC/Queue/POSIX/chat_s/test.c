
// #include <stdio.h>
// #include <string.h>
// #include <mqueue.h>  
// #include <errno.h>  

// #define MQ_MODE (S_IRUSR | S_IWUSR ) 
// char pathname[20] = "/myQueue" ;
// char str[20] = "Tuan Truong Nho";
// char mess[50];
// char messr[50];
// int main()
// {
//   //  struct mq_attr attr;
//     unsigned int priority;
//     mqd_t id = mq_open(pathname, O_RDWR | O_CREAT, MQ_MODE, NULL);
//     if (id == -1)
//     {
//         printf("Can not make queue\n");
//         return 0;
//     }
    

//     int check;
//   //  printf("Enter message from : ");
//   //  fgets(mess, 50, stdin);

//     check = mq_send(id, str, strlen(str), 0);
//     if (check == -1)
//     {
//         printf("Can not send message\n");
//     }

//     sleep(1);
//     check = mq_receive(id, messr, sizeof(messr),&priority );
//     if (check == -1)
//     {
//         printf("Can not send message\n");
//     }
//     printf("%s\n",messr);
    
    

//     mq_close(id);

//     mq_unlink(pathname);

//     return 0;
 //}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_NAME "/my_message_queue"
#define MAX_MSG_SIZE 1024

int main() {
    // Message queue attributes
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; // Maximum number of messages in the queue
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    // Create a message queue or open if it already exists
    mqd_t mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    // Sending a message
    char message[] = "Hello, Message Queue!";
    if (mq_send(mq, message, strlen(message) + 1, 0) == -1) {
        perror("mq_send");
        exit(EXIT_FAILURE);
    }
    printf("Message sent: %s\n", message);

    // Receiving a message
    char received_msg[MAX_MSG_SIZE];
    unsigned int priority;
    ssize_t received_bytes = mq_receive(mq, received_msg, sizeof(received_msg), &priority);
    if (received_bytes == -1) {
        perror("mq_receive");
        exit(EXIT_FAILURE);
    }

    printf("Received Message: %s\n", received_msg);

    // Close and unlink the message queue
    if (mq_close(mq) == -1) {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }
    if (mq_unlink(QUEUE_NAME) == -1) {
        perror("mq_unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}
