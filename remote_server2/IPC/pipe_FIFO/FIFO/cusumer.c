#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <unistd.h>

#define FIFO_FILE   "./myfifo1"
#define FIFO_FILEt   "./myfifo2"
char str2[50];
char str[50];
int fd ; 
int fdt ;

int main()
{
    mkfifo(FIFO_FILE, 0666);
    mkfifo(FIFO_FILEt, 0666);

    while(1)
    {
        fd = open(FIFO_FILE, O_RDONLY);
        read(fd, str, sizeof(str));
        printf("Producer message: %s", str);
        close (fd);

        fdt = open(FIFO_FILEt, O_WRONLY);
        printf("Message from consumer : ");
        fflush(stdin);
        fgets(str2, 50, stdin);
        write(fdt, str2, sizeof(str2));
        close (fdt);

    }
    return 0;
}