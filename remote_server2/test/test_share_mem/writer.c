#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <semaphore.h>

#define NAME_SEMA "/sema_test"
#define NAME_FILE "/test_m"
int main()
{
    sem_t *s = sem_open(NAME_SEMA,O_CREAT, 0666, 0 );

    if (s == SEM_FAILED){
        printf("Can not create semaphore\n");
        return -1;
    }

    int shm_id = shm_open(NAME_FILE, O_CREAT | O_RDWR, 0666);
    if (shm_id == -1)
    {
        printf("Can not create share mem fd\n");
        return -1;
    }

    if (ftruncate(shm_id, 100) == -1)
    {
        printf("Can not set size for share mem\n");
        return -1;
    }
    
    while(1)
    {
    char *start_add = (char *)mmap(0, 100, PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0);

    printf("Enter data to share memory: ");
    fgets(start_add, 50, stdin);
    
    sem_post(s);
    munmap(start_add, 100);
    }

    sem_close(s);

    close(shm_id);

    sem_unlink(NAME_SEMA);


    return 0;
}