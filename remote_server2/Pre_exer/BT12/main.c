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
    pthread_mutex_lock(&m);
 
    while(!i){
        pthread_cond_wait(&cond,&m);
    }
   // printf("i= %d\n",i);
    printf("Enter name: ");
    gets(p->name);
    printf("Enter born year: ");
    gets(p->born);
    printf("Enter hown town: ");
    gets(p->hown_town);
    i=0;
    //k=1;
    j=1;
    //l=0;
    int p1 = pthread_cond_signal(&condt);
    if (p1 == -1)
    {
        printf("Can not send signal from thread 1\n");
    }
    else{
        printf("Send signal OK from Thread 1\n");
    }
    pthread_mutex_unlock(&m);
   // sleep(1);
    }
}
static void *func2(void *para)
{
    while(1){
    pthread_mutex_lock(&m);
    while(!j){
        pthread_cond_wait(&condt,&m);
    }
    person *p= (person *)para;
    sprintf(str,"%s %s %s\n",p->name,p->born,p->hown_town);
    int w=write(fd,str,strlen(str));
    if (w==-1)
    {
        printf("Can not write data\n");
    }
    else{
        printf("Write to file successfully\n");
    }
    j=0;
    k=1;
    int p2 = pthread_cond_signal(&condk);
    if (p2 == -1)
    {
        printf("Can not send signal from thread 2\n");
    }
    else{
        printf("Send signal OK from Thread 2\n");
    }
    pthread_mutex_unlock(&m);
    }

   
}
static void *func3(void *para)
{
    while(1){
      //  printf("Check 0\n");
 
    pthread_mutex_lock(&m);
         printf("Check \n");
    while(!k){
    pthread_cond_wait(&condk,&m);
    }
    person *p= (person *)para;
    sprintf(readdata,"%s %s %s\n",p->name,p->born,p->hown_town);
    printf("%s",readdata);
    k=0;
    //l=1;
    i=1;
    int p3 = pthread_cond_signal(&cond);
    if (p3 == -1)
    {
        printf("Can not send signal from thread 3\n");
    }
    else{
        printf("Send signal OK from thread 3\n");
    }
    pthread_mutex_unlock(&m);
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
