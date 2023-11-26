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
    data *check = (data *)para;
    pthread_mutex_lock(&mux);
    printf("Start thread 1\n");
    printf("Nhap ten : ");
    gets(check->name);
    printf("Nhap infor : ");
    gets(check->infor);
    printf("Thong tin nhap la : %s %s\n",check->name, check->infor);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mux);
  //  pthread_mutex_lock(&mux1);
     while(count <8)
     {
        count++;
       // printf("%d ",count);
       //if (count ==5)
       //{
        //pthread_cond_signal(&cond1);
      // }
        sleep(1);
     }
  //    pthread_mutex_unlock(&mux1);
   
     pthread_exit(NULL);
  
}
static void *func2(void *para)
{
   // printf("Start thread 2\n");

    while(1)
    {

//     if (count ==5)
//     {
//         printf("OK\n");
//         break;

//    }
        //pthread_mutex_lock(&mux1);
        //pthread_cond_wait(&cond1,&mux1);
        printf("OK\n");
        sleep(1);
       // pthread_mutex_unlock(&mux1);


    }


 }
int main()
{
    data d;
    pthread_create(&id1, NULL, &func1,&d);
   pthread_create(&id2, NULL, &func2,NULL);
     pthread_mutex_lock(&mux);
     // pthread_mutex_lock(&mux1)
     pthread_cond_wait(&cond,&mux);
     
    while(1)
    {
        printf("Programming running\n");
        sleep(1);
    }
    pthread_mutex_unlock(&mux);

    return 0;
}