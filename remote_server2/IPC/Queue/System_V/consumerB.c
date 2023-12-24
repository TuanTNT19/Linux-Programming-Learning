#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

char pathname[20] = "./myqueue";

typedef struct{
    long type;
    char mess[50];
}buffer;

int main()
{
    key_t key = ftok(pathname, 50);
    buffer message;

    int id = msgget(key, IPC_CREAT | 0666);

   // printf("Enter type of message : ");
    //scanf("%d",&message.type);
    printf("Data receive : \n");
    msgrcv(id, &message, sizeof(message), 2, 0);

    printf("mess receive : %s",message.mess);
    printf("type receive: %ld\n",message.type);
    
    return 0;
}