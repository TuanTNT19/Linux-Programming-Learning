#include <sys/un.h>
#include <sys/socket.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char pathname[20] = "sock_stream";
void chat_fuc(int fd)
{
    char buff_r[50];
    char buff_s[50];

    while(1)
    {
        printf("Message to server: ");
        fgets(buff_s, 50, stdin);
        write(fd, buff_s, 50);

        printf("Message from server: ");
        read(fd, buff_r, 50);
        printf("%s",buff_r);

    }

    close(fd);
}
int main()
{
    int ser_fd;
    struct sockaddr_un servaddr;

    ser_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    
    servaddr.sun_family = AF_UNIX;
    strcpy(servaddr.sun_path, pathname);
    //servaddr.sun_path = "./sock_stream";

    connect(ser_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    chat_fuc(ser_fd);

    close(ser_fd);
    
    return 0;
}