#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>

int data=3; //share resouces
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER ;// khởi tạo tĩnh
int fd;
pthread_t id1,id2;
char str1[10]="Irene ";
char str2[14]="Bae Joo Huyn ";
typedef struct{
    char name[20];
    char Idol[20];
}data_check;
static void *func1(void *para)
{
   
    //data_check *data = (data_check *)para;

     printf("I am thead 1\n");
     pthread_mutex_lock(&m1);
     lseek(fd,0,SEEK_SET);
     int w1=write(fd,str1,strlen(str1));
     pthread_mutex_unlock(&m1);
     printf("End of thread 1\n");
    pthread_exit(NULL);

}
static void *func2(void *para)
{
   printf("I am thread 2\n");
     pthread_mutex_lock(&m1);
      // lseek(fd,1,SEEK_SET);
      int w2=write(fd,str2,strlen(str2));
     pthread_mutex_unlock(&m1);
     printf("End of thread 2\n");
    pthread_exit(NULL);
    //exit(1);

}
int main()
{
    data_check data={0};
    strncpy(data.name, "TuanTNT19",sizeof(data.name));
    strncpy(data.Idol, "Irene Bae",sizeof(data.Idol));
     fd=open("text.txt",O_RDWR | O_CREAT , 0667);
     if (fd ==-1)
     {
        printf("Can not open text.txt \n");
     }
    if (!pthread_create(&id1,NULL,&func1,&data))
    {
        printf("Create thread1\n");
    }
       
    if (!pthread_create(&id2,NULL,&func2,NULL))
    {
        printf("Create thread2\n");
    }
   // sleep(5);
   // pthread_cancel(id2);
   // sleep(2);
    //pthread_cancel(id1);
    pthread_join(id2,NULL);
    
    printf("OK ??\n");
    while(1);
    return 0;
}
