#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER ;// khởi tạo tĩnh
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_t id1,id2,id3;
typedef struct{
    char name[20];
    char que[10];
    char born[10];
}Sinhvien;
Sinhvien *SV;
int fd;
int i=0;
char nameread[20];
char queread[10];
char bornread[10];
static void *func1(void *para)
{
   
    SV= (Sinhvien *)para;
    pthread_mutex_lock(&m1);
    i++;
    if(i != 1)
    {
        pthread_cond_wait(&cond,&m1);
    }
    printf("I am thead 1\n");
    print("Nhap ten: \n");
    gets(SV->name);
    print("Nhap que quan: \n");
    gets(SV->que);
    printf("Nhap ngay sinh: \n");
    gets(SV->born);
    pthread_mutex_unlock(&m1);
}
static void *func2(void *para)
{
     printf("I am thead 2\n");
    write(fd,SV->name,sizeof(SV->name));
    write(fd,SV->que,sizeof(SV->que));
    write(fd,SV->born,sizeof(SV->born));
    write(fd,"\n",strlen("\n"));


}
static void *func3(void *para)
{
     
    // lseek(fd,0,);
    read(fd,nameread,sizeof(nameread));
    printf("%s ",nameread);
    read(fd,queread,sizeof(queread));
    printf("%s ",queread);
    read(fd,bornread,sizeof(bornread));
    printf("%s ",bornread);
    pthread_cond_signal(&cond);

}
int main()
{
      fd = open("text.txt",O_RDWR | O_CREAT | O_APPEND,0667);
    Sinhvien stu;
    
    if (!pthread_create(&id1,NULL,&func1,&stu))
    {
        printf("Create thread1\n");
    }
       
    if (!pthread_create(&id2,NULL,&func2,&stu))
    {
        printf("Create thread2\n");
    }
    if (!pthread_create(&id3,NULL,&func3,NULL))
    {
        printf("Create thread2\n");
    }

    while(1);
    return 0;
}
