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
    int ser_fd;
    struct sockaddr_un seraddr;

    ser_fd = socket(AF_UNIX, SOCK_DGRAM, 0);

    seraddr.sun_family = AF_UNIX;
    strcpy(seraddr.sun_path, pathname);

    while(1)
    {
        int len = sizeof(seraddr);

        printf("Message to server : ");
        fgets(buff_s, 50, stdin);
        sendto(ser_fd, buff_s, 50, 0, (struct sockaddr *)&seraddr, len);

        printf("Message from server: ");
        recvfrom(ser_fd, buff_r, 50, 0, (struct sockaddr *)&seraddr, &len);
        printf("%s\n",buff_r);
    }

    close(ser_fd);

    return 0;
}