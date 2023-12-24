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
        printf("Message from client : ");
        read(fd, buff_r, 50);
        printf("%s",buff_r);

        printf("Message to client : ");
        fgets(buff_s, 50, stdin);
        write(fd, buff_s, 50);

    }
    close(fd);
}
int main()
{
    int serv_fd, clie_fd;
    struct sockaddr_un svaddr, clieaddr;

    serv_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    svaddr.sun_family = AF_UNIX;
    strcpy(svaddr.sun_path, pathname);
    //svaddr.sun_path = "./sock_stream";

    bind(serv_fd, (struct sockaddr *)&svaddr, sizeof(svaddr));

    listen(serv_fd, 2);

    while(1)
    {
        int len = sizeof(clieaddr);
        clie_fd = accept(serv_fd,(struct sockaddr *)&clieaddr, &len);
        chat_fuc(clie_fd);
    }

    close(serv_fd);
    close(clie_fd);
    unlink("sock_stream");

    return 0;
}