// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <signal.h>
// #include <sys/types.h>
// #include <string.h>
// #include <sys/wait.h>

// char str1[30] = "Tuan TNT19 \n";
// char str2[20] = "Tuan Truong Nho\n";
// char str3[20] = "Truong Nho Tuan\n";
// char read_str[20];
// int r = 10;

// static void func(int signum)
// {
//     wait(NULL); 
//     printf("child process termination\n");
// }

// int main()
// {
//     int fds[2];
//     pid_t child_pid;

//     if (pipe(fds) < 0)
//     {
//         printf("Can not make pipe\n");
//     }

//     child_pid = fork();
//     if (child_pid >= 0)
//     {
//         if (child_pid == 0)
//         {
//             printf ("This is chilf process\n");
//             close(fds[1]);
//             while(1){
//             read(fds[0],read_str,sizeof(read_str));
//             printf("%s\n",read_str);
//             if (r == 0)
//             {
//                 printf("End of pipe \n");
//                 break;
//             }
//             }
//             printf("End of process child\n");
//         }
//         else{
//             signal(SIGCHLD, func);
//             printf("This is parrent process\n");
            
//             write(fds[1],str1,strlen(str1));
//             write(fds[1],str2,strlen(str2));
//             write(fds[1],str3,strlen(str3));

//             close(fds[1]);
//             //sleep(2);
//         }
//     }
//     else {
//         printf("Can not fork \n");

//     }
    
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSG_SIZE    16
int fds[2];
char *msg1 = "hello, world #1";
char *msg2 = "hello, world #2";
char *msg3 = "hello, world #3";

void handler(int num)
{
    write(fds[1],"hello, world #4",16);
}
static void func(int signum)
{
    wait(NULL); 
    printf("child process termination\n");
}

int main(int argc, char const *argv[])
{
    /* code */
    char in_buff[MSG_SIZE];
    int num_read = 0;

    pid_t child_pid;

   //signal(SIGINT, handler);

    if (pipe(fds) < 0) {
        printf("pipe() unsuccessfully\n");
        exit(1);
    }

    child_pid = fork();
    if (child_pid >= 0) {
        if (child_pid == 0) {
            // Do something
            // printf("I am Child\n"); // reader
            if (close(fds[1]) == -1) // write end is unused
               printf("close(fds[1]) failed\n");
            
            // // Suspend if no data
            // close(fds[1]);
            while (1 ) {
                num_read = read(fds[0], in_buff, MSG_SIZE);
                printf("Unblock read\n");
                if (num_read == -1) {
                    printf("read() failed\n");
                    exit(0);
                } else if (num_read == 0) {
                    printf("pipe end-of-pipe\n");
                    break;
                } else {
                    printf("msg: %s\n", in_buff);
                }
            };
            //close(fds[0]);
            printf("End of process child\n");

        } else { 
            // Prevent zombie process 
            signal(SIGCHLD, func);
            //close(fds[0]);
            printf("I am Parent\n"); // writer
            //if (close(fds[0]) == -1) // read end is unused
              //  printf("close(fds[0]) failed\n");

            // Write into pipe
            write(fds[1], msg1, MSG_SIZE);
            write(fds[1], msg2, MSG_SIZE);
            write(fds[1], msg3, MSG_SIZE);

            if (close(fds[1]) == -1) // reader will see end-of-pipe
                printf("close(fds[0]) failed\n");
          // close(fds[1]);
            while(1);
        }
    } else {
        printf("fork() unsuccessfully\n");
    }

    return 0;
}