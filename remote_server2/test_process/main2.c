
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    int i;
    int num_processes = 3; // Number of processes to create
    int fd;
    fd = open("text.txt",O_RDWR | O_CREAT, 0667);
    char buff1[12]="Tuan Truong\n";
    char buff2[14]="Bae Joo Huyn\n";
    char buff3[6]="Irene\n";
    for (i = 0; i < num_processes; i++) {
        pid_t child_pid = fork();

        // Check for errors in fork()

        // Code executed by child process
        if (child_pid == 0) {
            printf("Child process %d, PID: %d\n", i + 1, getpid());
            if (i+1==1)
            {
                printf("Tao la tien trinh con 1\n");
                lseek(fd,0,SEEK_SET);
                write(fd,buff1,sizeof(buff1));
            }
            if (i+1==2)
            {
                printf("Tao la tien trinh con 2\n");
                lseek(fd,14,SEEK_SET);
                write(fd,buff2,sizeof(buff2));
            }
            if (i+1==3)
            {
                printf("Tao la tien trinh con 3\n");
                lseek(fd,29,SEEK_SET);
                write(fd,buff3,sizeof(buff3));
            }
            // Child process should exit to prevent it from creating more processes
            return 0;
        }
 
    }

    // Code executed by the parent process
    printf("Parent process, PID: %d\n", getpid());
    close(fd);
    // Parent process should wait for all child processes to complete
    for (i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    return 0;
}

