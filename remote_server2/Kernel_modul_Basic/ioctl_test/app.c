#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>

#define DEVICE_PATH "/dev/my_device"


#define ON _IOW('a', '1', int)
#define OFF _IOW('a', '0', int)

int main()
{
    int choice;

    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0)
    {
        printf("Can not open path device\n");
        return -1;
    }

    while(1)
    {
    printf("Enter your chosen: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Send ON to kernel\n");
        ioctl(fd, ON, NULL);
    }
    else if (choice == 0)
    {
        printf("send OFF to kernel\n");
        ioctl(fd, OFF, NULL);
    }
    else{
        printf("chosen is not valid\n");

    }

    }

    return 0;

}
