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
static void *func(void *para)
{
    pthread_t tid = pthread_self();
    data_check *data = (data_check *)para;
    if (pthread_equal(tid,id1))
    {
        printf("I am thread 1\n");
    }
    else{
        printf("I am thead 2\n");
        printf("%s %s\n",data->Idol, data->name);
    }

}
int main()
{
    data_check data={0};
    strncpy(data.name, "TuanTNT19",sizeof(data.name));
    strncpy(data.Idol, "Irene Bae",sizeof(data.Idol));
    
    if (!pthread_create(&id1,NULL,&func,NULL))
    {
        printf("Create thread1\n");
    }
       
    if (!pthread_create(&id2,NULL,&func,&data))
    {
        printf("Create thread2\n");
    }
    sleep(1);
    return 0;
}