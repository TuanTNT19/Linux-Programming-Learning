#include <stdio.h>
#include <string.h>
#include <mqueue.h>  
#include <errno.h>  

#define MQ_MODE (S_IRUSR | S_IWUSR ) 

struct s {
        char name[50];
        int age;
        char home_town[20];
        char sdt[10]; 
};
typedef struct{
    long prio;
    struct s sinhvien;

} message;

int main()
{
    message sv;
    long mssv;
    int t ;
    int c;
    int n = 0;
    int temp =0;

    struct mq_attr attr;
    //set max message and max size of a message
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    
    mqd_t mqid = mq_open("/mqueue", O_RDWR | O_CREAT | O_NONBLOCK , MQ_MODE, &attr);  //open queue
      if (mqid == -1) {  
        printf("mq_open() error %d: %s\n", errno, strerror(errno));  
        return -2;  
    } 


//Nhap thong tin sinh vien
    do{
       n++;
       printf("Enter Information: \n");
       printf("Mssv : ");
       scanf("%ld",&sv.prio);
       getchar();
       printf("Name : ");
       fgets(sv.sinhvien.name, 50, stdin);
       printf("Age : ");
       scanf("%d",&sv.sinhvien.age);
       getchar();
       printf("HomeTown: ");
       fgets(sv.sinhvien.home_town, 20, stdin);
       printf("Phone: ");
       fgets(sv.sinhvien.sdt, 10, stdin);

       mq_send(mqid, &sv, sizeof(message), sv.prio); //send infor to mqueue


       printf("Continue entering information: ");
       printf("\n 1. YES       0. NO\n");
       printf("Your chosen: ");
       scanf("%d",&t);
       getchar();
    }
    while(t);

//menu 
    do{
       printf("1. Display all infor\n");
       printf("2. Display a infor with MSSV\n");
       printf("3. Delete a infor\n");
       printf("0. Cancel \n");
       printf("Your chosen: ");
       scanf("%d",&c);

       temp = n; // set temp to value of number infor
       if (c == 1)
       {
           while(temp --){
           mq_receive(mqid, (char *)&sv, 120,NULL);   //receive and delete a infor in mqueue
           printf("%ld %s %d %s %s\n",sv.prio, sv.sinhvien.name, sv.sinhvien.age, sv.sinhvien.home_town, sv.sinhvien.sdt); //print that infor
           mq_send(mqid, &sv, sizeof(sv), NULL);    //send ( push ) that infor to mqueue again
    
        }

       }
       
       else if (c == 2)
       {
            printf("Enter MSSV need finding: ");
            scanf("%ld",&mssv);

            while(temp --){
            mq_receive(mqid, (char *)&sv, 120,NULL); //receive and delete a infor in mqueue

            if (sv.prio == mssv) //check MSSV:  if MSSV valid, print that infor
            {
            printf("%ld %s %d %s %s\n",sv.prio, sv.sinhvien.name, sv.sinhvien.age, sv.sinhvien.home_town, sv.sinhvien.sdt);
            }

            mq_send(mqid, &sv, sizeof(message), NULL); //send ( push ) that infor to mqueue again
    
       }

       }

       else if (c == 3 )
       {
            printf("Enter MSSV need deleting: ");
            scanf("%ld",&mssv);

            while(temp --)
            {
            mq_receive(mqid, (char *)&sv, 120,NULL); //receive and delete a infor in mqueue

            if (sv.prio != mssv)   //check MSSV : if MSSV does not valid, push back that infor
            {
            mq_send(mqid, &sv, sizeof(message), NULL);  //send ( push ) that infor to mqueue again
            }

            else //if MSSV valid, delete that infor and decrease n ( number of infor )
            {
            n--;
            }
           }
       }
    }
    while(c);

    printf("End of Program\n");

    mq_close(mqid); //close queue id
    if (mq_unlink("/mqueue") == -1) //remove mqueue
    {
        printf("Can not delete Queue\n");
    }
    else{
        printf("Unlink OK\n");
    }

    return 0;
}