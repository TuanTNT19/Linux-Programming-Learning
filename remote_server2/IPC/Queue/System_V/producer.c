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

    while(1){
    
    printf("Enter type of message : ");
    scanf("%ld",&message.type);
    getchar();
    printf("Enter data of message : ");
    fgets(message.mess, 50, stdin);

    msgsnd(id, &message, sizeof(message), 0);
    }
    
    msgctl(id, IPC_RMID, NULL);
    
    return 0;
}