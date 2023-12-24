
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    key_t key = ftok("./shmfile",65);

    int shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        printf ("Can not create share memory segment\n");
    }
    
    char *str = (char *)shmat(shmid, NULL, 0);

    while(1){
    printf("Enter some data to memory share: ");
    fgets(str, 1024, stdin);
    }
    
    shmdt(str);

    return 0;
}