#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_NAME "/my_message_queue"
#define MAX_MSG_SIZE 1024

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char received_msg[MAX_MSG_SIZE];
    unsigned int priority;

    // Message queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; // Maximum number of messages in the queue
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    // Open the message queue for reading
    mq = mq_open(QUEUE_NAME, O_RDONLY, 0666, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    // Receiving a message
    ssize_t received_bytes = mq_receive(mq, received_msg, MAX_MSG_SIZE, &priority);
    if (received_bytes == -1) {
        perror("mq_receive");
        exit(EXIT_FAILURE);
    }

    printf("Received Message: %s\n", received_msg);

    // Close the message queue
    if (mq_close(mq) == -1) {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }

    return 0;
}
