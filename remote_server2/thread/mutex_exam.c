#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
int data=3; //share resouces
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER ;// khởi tạo tĩnh
pthread_t id1,id2;
typedef struct{
    char name[20];
    char Idol[20];
}data_check;
static void *func1(void *para)
{
   
    //data_check *data = (data_check *)para;

    printf("I am thead 1\n");
     pthread_mutex_lock(&m1);
     data++;
     printf("Value of Data by thread 1: %d\n",data);
     sleep(5);
     pthread_mutex_unlock(&m1);
    pthread_exit(NULL);

}
static void *func2(void *para)
{
   printf("I am thread 2\n");
     pthread_mutex_lock(&m1);
     data+=2;
     printf("Value of Data by thread 2: %d\n",data);
     pthread_mutex_unlock(&m1);
    pthread_exit(NULL);
    //exit(1);

}
int main()
{
    data_check data={0};
    strncpy(data.name, "TuanTNT19",sizeof(data.name));
    strncpy(data.Idol, "Irene Bae",sizeof(data.Idol));
    
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