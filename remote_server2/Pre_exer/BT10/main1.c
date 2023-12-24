#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

char str[5];
int main()
{
    clock_t start_time = clock();//timer counter start

    //create file txt1
    int fd =  open ("text1.txt", O_RDWR | O_APPEND | O_CREAT,0667);
    if (fd == -1){
        printf("Can not open file txt1 \n");
    }

    //write number from 0 to 999999 to file
    for (int i=0;i<1000000;i++)
    {
        sprintf(str,"%d \n",i);
        write(fd,str,sizeof(str));
    }

    clock_t  end_time = clock();//timer counter end
    double time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time_used: %f",time_used);
    
    close(fd);

    return 0;
}
