#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>

#define SHARED_MEM_SIZE     100             /* the size (in bytes) of shared memory object */
#define FILE_NAME           "phong_mmap"     /* name of the shared memory object */

int main()
{
    int shm_id = shm_open(FILE_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_id == -1)
    {
        printf("Can not create share memnory POSIX\n");
    }
    
    ftruncate(shm_id, 100);

    char *str = (char *)mmap(0, 100, PROT_WRITE | PROT_READ, MAP_SHARED, shm_id, 0);

    printf("Read data from POSIX share memory: ");
    printf("%s\n", str);

    munmap(str, 100);
    close (shm_id);
   // shm_unlink(FILE_NAME);

    return 0;

}