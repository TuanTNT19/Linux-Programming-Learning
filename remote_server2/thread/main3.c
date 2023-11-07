#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t id1,id2;
typedef struct{
    char name[20];
    char Idol[20];
}data_check;
static void *func1(void *para)
{
   
    data_check *data = (data_check *)para;

    printf("I am thead 1\n");
    while(1)
    {
    printf("%s %s\n",data->Idol, data->name);
    sleep(1);
    }
   // pthread_exit(NULL);

}
static void *func2(void *para)
{
   printf("I am thread 2\n");
   //int t=4;
   while(1)
   {
    printf("Hello Tuan\n");
    sleep(1);
   }
    //pthread_exit(NULL);

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
    sleep(5);
    pthread_cancel(id2);
    sleep(2);
    pthread_cancel(id1);
    while(1);
    return 0;
}