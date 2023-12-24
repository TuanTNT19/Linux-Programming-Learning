#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>     //  Chứa cấu trúc cần thiết cho socket. 
#include <netinet/in.h>     //  Thư viện chứa các hằng số, cấu trúc khi sử dụng địa chỉ trên internet
#include <arpa/inet.h>
#include <unistd.h>

void chat_func(int fd)
{
    char buff_r[50];
    char buff_s[50];

    while(1)
    {
        printf("Message to server: ");
        fgets(buff_s, 50, stdin);
        write(fd, buff_s, 50);

        printf("Message from server : ");
        read(fd, buff_r, 50);
        printf("%s",buff_r);
    }

    close(fd);
}

int main(int argc, char *argv[])
{
    int ser_fd;
    int port;
    struct sockaddr_in serv_addr;

    ser_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    port = atoi(argv[2]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);

    connect(ser_fd, (struct sockaddr* )&serv_addr, sizeof(serv_addr));

    chat_func(ser_fd);

    close(ser_fd);
    return 0;
}