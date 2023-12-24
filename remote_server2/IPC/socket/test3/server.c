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
        printf("Message from Client : ");
        read(fd, buff_r, sizeof(buff_r));
        printf("%s\n",buff_r);

        printf("Message to Client : ");
        fgets(buff_s, 50, stdin);
        write(fd, buff_s, 50);
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    int ser_fd , port, client_fd;

    ser_fd = socket (AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in serv_addr, client_addr;
    port = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Use any available interface

    bind(ser_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    
    listen(ser_fd, 2);
    
    int len = sizeof(client_addr);
    while(1)
    {
        client_fd = accept(ser_fd, (struct sockaddr *)&client_addr, (socklen_t *)&len);
        chat_func(client_fd);
    }

    close(ser_fd);

    return 0;
}