#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>     //  Chứa cấu trúc cần thiết cho socket. 
#include <netinet/in.h>     //  Thư viện chứa các hằng số, cấu trúc khi sử dụng địa chỉ trên internet
#include <arpa/inet.h>
#include <unistd.h>

void chat_func(int socket_fd)
{
    char data_send[50];
    char data_receive[50];
    
    while(1)
    {
        printf("Please enter message : ");
        gets(data_send);

        int nw = write(socket_fd, data_send, sizeof(data_send));
        if (nw == -1)
        {
            printf("Can not write data\n");
        }

        int nr = read(socket_fd, data_receive, sizeof(data_receive));
        if (nr == -1)
        {
            printf("Can not read data\n");
        }
        
        printf("Message from sever : %s\n",data_receive);


    }
    close(socket_fd);
}
int main(int argc, char *argv[])
{
    int client_fd ;
    struct sockaddr_in serv_addr;
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1)
    {
        printf("Can not make socket in client \n");
    }

    int port = atoi(argv[2]);
    inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
   // serv_addr.sin_addr.s_addr = htonl(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(port); 
    if( connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr) )==-1)
    {
        printf("Can not connent to sever\n");
    }
    chat_func(client_fd);
    return 0;
}
