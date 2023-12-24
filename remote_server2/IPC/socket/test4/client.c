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
    int ser_fd;
    struct sockaddr_in serv_add;

    ser_fd = socket(AF_INET, SOCK_DGRAM, 0);

    serv_add.sin_family = AF_INET;
    serv_add.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &serv_add.sin_addr);

    while(1)
    {
        len = sizeof(serv_add);
        printf("Message to server: ");
        fgets(buff_s, 50, stdin);
        sendto(ser_fd, buff_s, 50, 0, (struct sockaddr *)&serv_add, sizeof(serv_add));

        printf("Message from server: ");
        recvfrom(ser_fd, buff_r, 50, 0, (struct sockaddr *)&serv_add, &len);
        printf("%s",buff_r);
    } 

    close(ser_fd);


    return 0;
}