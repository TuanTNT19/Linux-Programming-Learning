// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <pthread.h>
// #include <fcntl.h>
// typedef struct{
//     char name[20];
//     char tuoi[2];
// }infor_t;
// char readchar[50];
// char str[26];
// int main()
// {
//     infor_t person;
//     int fd = open("text.txt",O_RDWR | O_CREAT | O_APPEND,0667);
//     if (fd ==-1)
//     {
//         printf("Can not create file txt\n");
//     }
//     printf("Nhap name : ");
//     gets(person.name);
//     printf("Nhap tuoi: ");
//     gets(person.tuoi);
//     sprintf(str,"%s %s \n",person.name,person.tuoi);
//     int w1 = write(fd,str,strlen(str));
//     if (w1==-1)
//     {
//         printf("Can not write name \n");
//     }
//     //sleep(1);
//     lseek(fd,0,SEEK_SET);
//     int r = read(fd,readchar,sizeof(readchar));
//     printf("%s\n",readchar);
//     close(fd);
//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER ;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t condt = PTHREAD_COND_INITIALIZER;
pthread_cond_t condk = PTHREAD_COND_INITIALIZER;

pthread_t id1,id2,id3;
typedef struct{
    char name[20];
    char born[10];
    char hown_town[20];
}person;

char str[52];
char readdata[52];
int fd;
int i=1;
int k=0;
int j=0;
int l=1;

static void *func1(void *para)
{
    while(1){
    person *p= (person *)para;
    while(!i){
        pthread_cond_wait(&cond,&m);
    }
    printf("l = %d \n",l);
    l++;
    pthread_mutex_lock(&m);
    printf("Send ....1\n");
    i=0;
    j=1;
    int p1 = pthread_cond_signal(&condt);
    printf("Send ok 1 \n");
    //sleep(1);
    pthread_mutex_unlock(&m);
    //sleep(1);
    }
 
}
static void *func2(void *para)
{
    while(1){
    pthread_mutex_lock(&m);
    while(!j){
        pthread_cond_wait(&condt,&m);
    }
   printf("Wait ok\n");
   printf("Send ...2\n");
   j=0;
   k=1;
  int p1 = pthread_cond_signal(&condk);
   printf("Send ok ...2\n");
   pthread_mutex_unlock(&m);
    }

 }
static void *func3(void *para)
{
    while(1){
      //  printf("Check 0\n");
 
    pthread_mutex_lock(&m);
    while(!k){
    pthread_cond_wait(&condk,&m);
    }
    printf("Wait ok\n");
   printf("Send ...3\n");
   k=0;
   i=1;
  int p1 = pthread_cond_signal(&cond);
   printf("Send ok ...3\n");
    pthread_mutex_unlock(&m);
   // sleep(1);
   }

}
int main()
{
    person pe;
    fd = open("text.txt",O_RDWR | O_CREAT | O_APPEND,0667);
    
    if (pthread_create(&id1,NULL,&func1,&pe))
    {
        printf("Create thread1 error\n");
    }
       
    if (pthread_create(&id2,NULL,&func2,&pe))
    {
        printf("Create thread2 error\n");
    }
    if (pthread_create(&id3,NULL,&func3,&pe))
    {
        printf("Create thread3 error\n");
    }

    while(1);
    close(fd);
    return 0;
}
