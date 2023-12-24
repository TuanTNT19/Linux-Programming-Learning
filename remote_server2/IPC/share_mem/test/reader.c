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

  //  while(1)
   // {
    printf("Data in memory segment : ");
    printf("\n%s",str);
    //sleep(2);
    //}
    
    
    shmdt(str);

   // shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
