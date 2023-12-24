#include <sys/un.h>
#include <sys/socket.h>
#include <stddef.h>
#include <stdio.h>

#define BUF_SIZE 10 
#define SOCK_PATH "./sock_stream"
char send_d[50];
char receive_f[50];
int main()
{
    int fd;
    struct sockaddr_un svaddr;

    fd = socket(AF_UNIX, SOCK_STREAM, 0); 
    if ( fd == -1)
    {
        printf("Can not make socket\n");

    }

    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path)-1);

    if (connect(fd, (struct sockaddr*)&svaddr, sizeof(struct sockaddr)) != 0) 
	{ 
        printf("connection with the server failed...\n"); 
    } 
    else{
        printf("Connect to the server\n");
        printf("Message send: ");
        gets(send_d);
        write(fd, send_d,sizeof(send_d));
    }
    while(1)
    {
        printf("From server: ");
        read(fd,receive_f,sizeof(receive_f));
        printf("%s\n",receive_f);
    }
    return 0;
    
}