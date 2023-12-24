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
    char send_data[50];
    char receive_data[50];

    while(1)
    {
        int nr = read(socket_fd, receive_data, sizeof(receive_data));
        if (nr == -1)
        {
            printf(" Can not read data\n");
        }
        printf("Message from client : %s\n",receive_data);
        printf("Please response client message: ");
        gets(send_data);
        int nw = write(socket_fd, send_data, sizeof(send_data));
        if (nw == -1)
        {
            printf("Can not send data \n");
        }
        sleep(1);
    }
    close (socket_fd);
}
int main(int argc, char *argv[])
{
    int sever_fd,port_no, client_fd;
    struct sockaddr_in serv_addr, client_addr;
    
    port_no = atoi(argv[1]);

    sever_fd = socket(AF_INET, SOCK_STREAM , 0);
    if (sever_fd == -1 )
    {
        printf("Can not make socket() in sever\n");
    }
    serv_addr.sin_family = AF_INET ;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
     
    if (bind(sever_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr) )){
        printf("Can not bind\n");
    }

    if (listen(sever_fd, 6) == -1){
        printf("Can not listen\n");
    }
    
    int len = sizeof(client_addr);
    client_fd = accept(sever_fd,(struct sockaddr*)&client_addr, (socklen_t *)&len);
    if (client_fd == -1)
    {
        printf("Can not accept \n");
    }
    else{
        chat_func(client_fd);

    }

    close(sever_fd);
    return 0;
}