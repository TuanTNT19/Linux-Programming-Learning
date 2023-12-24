#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FIFO_FILE   "./myfifo1"
#define FIFO_FILEt   "./myfifo2"
char str2[50];
char str[50];
char str3[50];
char str4[50];
int fd1 ; 
int fd2 ;
int fd3 ;
int fd4 ;
void func(int signum)
{
    printf("Im in func()\n");
    wait(NULL);
}

int main()
{
    pid_t child_pid = fork();
    
    if (child_pid >= 0) {
        if (child_pid == 0) {
            printf("I am Child, myPID: %d\n", getpid());
            mkfifo (FIFO_FILE, 0666);
            mkfifo (FIFO_FILEt, 0666);
            while(1)
            {
                fd1 = open (FIFO_FILE, O_RDONLY);
                read(fd1, str2, sizeof(str2));
                printf("Message from child : %s",str2);
                close (fd1);

                fd2 = open(FIFO_FILEt, O_WRONLY);
                printf("Message to parrent : ");
                fflush(stdin);
                fgets(str, 50, stdin);
                write(fd2,str, strlen(str));
                close (fd2);
            }
           
        } else {
            /**When a child is terminated, a corresponding SIGCHLD signal 
             * is delivered to the parent
            */
            signal(SIGCHLD, func);
            printf("I am Parent , my PID : %d\n",getpid());
            mkfifo (FIFO_FILE, 0666);
            mkfifo (FIFO_FILEt, 0666);
            while(1){
                fd3 = open(FIFO_FILE, O_WRONLY);
                printf("Message to child : ");
                fflush(stdin);
                fgets(str3, 50, stdin);
                write(fd3, str3, strlen(str3));
                close (fd3);

                fd4 = open(FIFO_FILEt, O_RDONLY);
                read(fd4, str4, 50);
                printf("Message from parrent : %s",str4);
                close(fd4);
            }
        }
    } else {
        printf("fork() unsuccessfully\n");
    }
}