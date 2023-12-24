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

    while(1)
    {
        fd = open(FIFO_FILE, O_WRONLY);
        printf("Message to consumer: ");
        fflush(stdin);
        fgets(str, 50 , stdin);
        write(fd, str, strlen(str)+1);
        close(fd);

        fdt = open(FIFO_FILEt, O_RDONLY);
        read(fdt, str2, sizeof(str2));
        printf("Consumer Message : %s", str2);
        close(fdt);


    }

    return 0;
  
}