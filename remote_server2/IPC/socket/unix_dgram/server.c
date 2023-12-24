#include <sys/un.h>
#include <sys/socket.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char pathname[20] = "sock_dgram";
char buff_r[50];
char buff_s[50];

int main()
{
    int serv_fd, clie_fd;
    struct sockaddr_un seraddr, clieaddr;

    serv_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    
    seraddr.sun_family = AF_UNIX;
    strcpy(seraddr.sun_path, pathname);

    bind(serv_fd, (struct sockaddr *)&seraddr, sizeof(seraddr));

    while(1)
    {
        int len = sizeof(clieaddr);
        printf("Message from client : ");
        recvfrom(serv_fd,buff_r, 50, 0, (struct sockaddr *)&clieaddr,&len );
        printf("%s\n",buff_r);

        printf("Message to client : ");
        fgets(buff_s, 50, stdin);
        sendto(serv_fd, buff_s, 50, 0, (struct sockaddr *)&clieaddr, len);

    }

    close (serv_fd);
    close(clie_fd);

    return 0;
}