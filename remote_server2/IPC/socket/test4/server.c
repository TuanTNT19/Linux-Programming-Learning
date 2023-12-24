#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>



char buff_r[50];
char buff_s[50];
int len = 0;

int main(int argc, char *argv[])
{
    int serv_fd;
    struct sockaddr_in svaddr, claddr;

    serv_fd = socket(AF_INET, SOCK_DGRAM, 0);

    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(atoi(argv[1]));
    svaddr.sin_addr.s_addr = INADDR_ANY;

    bind(serv_fd, (struct sockaddr *)&svaddr,sizeof(svaddr));
    
    while (1)
    {
        len = sizeof(claddr);
        printf("Message from client : ");
        recvfrom(serv_fd,buff_r, 50, 0,  (struct sockaddr *)&claddr, (socklen_t *)&len);
        printf("%s",buff_r);

        printf("Message to client : ");
        fgets(buff_s, 50, stdin);
        sendto(serv_fd, buff_s, 50, 0, (struct sockaddr *)&claddr, (sizeof(claddr)));

    }

    close(serv_fd);
    
    return 0;
}