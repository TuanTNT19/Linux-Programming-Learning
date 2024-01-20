#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

/*****************************************************************
 *                         MACROS
 *****************************************************************/
#define MAX_CONNECTIONS 2
#define MAX_BACKLOG     15
#define MAX_MSG_SIZE    100
#define TERMINATE_CODE  "0x59"


/*****************************************************************
 *                         STRUCTURES
 *****************************************************************/

typedef struct{
    int id;
    int fd;
    int port_num;
    char my_ip[50];
    struct sockaddr_in addr;
} device;


pthread_t Accep_Thread_id, Recei_Thread_id;

device this_device = {0};

device device_connect_to[MAX_BACKLOG] = {0};

device device_connect_from[MAX_BACKLOG] = {0};

int total_device_from = 0;
int total_device_to = 0;

char command[120];
char command_option[20];

stictic void *receive_from(void *para)
{
    device *devicet = (device *)para;

    char buff_r[100];

    while(1)
    {
        if (read(devicet->fd, buff_r, 100) < 0)
        {
            printf("Can not read data\n");
            return NULL;
        }

    if ((devicet->fd) >= 0){
    printf("** Message receive from: %s\n", devicet->my_ip);
    printf("** Sender Port:          %d\n",devicet->port_num);
    printf("-> Message:              %s\n", buff_r);
    }
    else {
        printf("Notification: %s\n", buff_r);
    }
    }       
}

static void *Accep_Thread(void *para)
{
    int client_fd;
    sockaddr_in cli_addr;
    socklen_t len = sizeof(cli_addr);

    while(1)
    {
        client_fd = accept(this_device.fd, (struct sockaddr *)&cli_addr, &len);

        device_connect_from[total_device_from].fd = client_fd;
        device_connect_from[total_device_from].id = total_device_from++;
        device_connect_from[total_device_from].addr = cli_addr;

        device_connect_from[total_device_from].port_num = ntohs(cli_addr.sin_port);
        inet_ntop(AF_INET, &cli_addr.sin_addr, device_connect_from[total_device_from].my_ip, 50);

    printf("                            ******                                   ");
    printf("\nAccept a new connection from IP addreass: %s, setup at port: %d\n", device_connect_from[total_device_from].my_ip, device_connect_from[total_device_from].port_num);
    
    if (pthread_create(&Recei_Thread_id, NULL, &receive_from, &device_connect_from[total_device_from])){
      printf("Can not receive message\n");
   }
    }
}

int send_to( device dev, char *mes)
{
    if (write(dev.fd, mes, 100) < 0)
    {
        printf("Can not send message\n");
        return 0;
    }

    return 1;
}

int connect_to(device dev)
{
    if (connect(dev.fd, (struct sockaddr *)&dev.addr, sizeof(dev.addr)) < 0)
    {
        return -1;
    }

    return 0;
}

void terminate_id(device dev)
{
    char str[70];
    sprintf(str, "The connection at port %d has just been terminated\n",dev.port_num);
    send_to(dev, str);

    dev.fd = -1;
}
int main()
{


    system("clear");

    this_device.fd = socket(AF_INET, SOCK_STREAM, 0);

    this_device.port_num = atoi(argv[1]);

    this_device.addr.sin_family = AF_INET;
    this_device.addr.sin_port = htons(this_device.port_num);
    this_device.addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(this_device.fd, (struct sockaddr*)&this_device.addr, sizeof(this_device.addr))==-1)
    {
        printf("ERROR: Can not make bind for this socket\n");
        return 0;
    }

    if (listen(this_device.fd, MAX_BACKLOG) == -1)
    {
        printf("ERROR: Can not listen for this device\n");
        return 0;
    }

    printf("Listening on port : %d\n", this_device.port_num);
    if (pthread_create(&Accep_Thread_id, NULL, &Accep_Thread, NULL)){
        printf("ERROR: Can not create thread for accept new device\n");
        return 0;
    }

    while(1){
        printf("Enter your command : ");
        fgets(command, 120, stdin);

        sscanf(command,"%s", command_option);

        if (!strcmp(command_option,"connect"))
        {
            char temp[10];
            char ip[20];
            int port_n;

            sscanf(command,"%s %s %d", temp, ip, &port_n);
            device_connect_to[total_device_to].fd = socket(AF_INET, SOCK_STREAM, 0);
            device_connect_to[total_device_to].id = total_device_to;
            device_connect_to[total_device_to].port_num = port_n;
            strcpy( device_connect_to[total_device_to].my_ip, ip);
             device_connect_to[total_device_to].addr.sin_port = htons(port_n);
             device_connect_to[total_device_to].addr.sin_family = AF_INET;
            inet_pton(AF_INET, device_connect_to[total_device_to].my_ip, &device_connect_to[total_device_to].addr.sin_addr);

        if (connect_to(device_connect_to[total_device_to])){
            printf("CAn not connect to new device\n");
        }

        else {
            printf("Connect OK\n");
            total_device_to ++;
        }

        }

        if (!(strcmp(command_option, "send")))
        {
            char temp[10];
            char message[100];
            int id;

            sscanf(command, "%s %d %[^\n]", temp, &id, message);

            for (int i=0; i< total_device_to; i++)
            {
                if (id == device_connect_to[i].id)
                {
                    send_to(device_connect_to[total_device_to], message);
                }
            }
        }
    }

    if !(strcmp(command_option))

    
}