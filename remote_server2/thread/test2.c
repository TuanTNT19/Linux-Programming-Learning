#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
pthread_mutex_t mux=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mux1=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_t id1, id2;
int count =0;
typedef struct{
    char name[10];
    char infor[20];
}data;
//data *check;
static void *func1(void *para)
{
    pthread_mutex_lock(&mux);
    while(count<8)
    {
    count++;
    printf("%d ",count);
    if (count==5)
    {
        pthread_cond_signal(&cond);
    }
    sleep(1);
    }
    printf("Shot\n");
   // pthread_cond_signal(&cond);
    printf("Shoted\n");
    pthread_mutex_unlock(&mux);


  
}
static void *func2(void *para)
{
   
   //while(1)
 //  {
    printf("Thread 2\n");
      // pthread_mutex_lock(&mux);
       while(1)
       {
       //while(count<5)
       //{
       //pthread_cond_wait(&cond,&mux);
       //printf("Check signal OK\n");
       //break;
      // }
       printf("thread 2\n");
       sleep(1);
       }
      // pthread_mutex_unlock(&mux);
       pthread_exit(NULL);

   //}


 }
int main()
{
    data d;
    pthread_create(&id1, NULL, &func1,NULL);
    pthread_create(&id2, NULL, &func2,NULL);
    pthread_mutex_lock(&mux);
    while (1)
    {
      pthread_cond_wait(&cond,&mux);
      printf("check OK\n");
      sleep(1);
      break;
    }
    pthread_mutex_unlock(&mux);
    
   
    return 0;
}