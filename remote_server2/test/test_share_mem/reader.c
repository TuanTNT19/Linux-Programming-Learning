#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <semaphore.h>

#define NAME_FILE "/test_m"
#define NAME_SEMA "/sema_test"

int main() {
    sem_t *s = sem_open(NAME_SEMA,O_CREAT, 0666, 0);

    if (s == SEM_FAILED){
        printf("Can not create semaphore\n");
        return -1;
    } 

    int shm_id = shm_open(NAME_FILE, O_CREAT | O_RDWR, 0666);
    if (shm_id == -1) {
        perror("Can not create share mem fd");
        return -1;
    }

    if (ftruncate(shm_id, 100) == -1) {
        perror("Can not set size for share mem");
        return -1;
    }

    while(1){

    char *start_add = (char *)mmap(0, 100, PROT_READ | PROT_WRITE, MAP_PRIVATE, shm_id, 0);
    
   
    sem_wait(s);
    // Đọc dữ liệu từ vùng nhớ chia sẻ
    printf("Data in share memory: %s\n", start_add);

    munmap(start_add, 100);
    }
    
    sem_close(s);
    close(shm_id);

    return 0;
}
