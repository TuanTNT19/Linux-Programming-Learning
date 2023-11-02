#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    printf("Run command <ls -lah> after 2 s\n");
    sleep(2);
    execl("/bin/ls","ls","-l","-a","-h",NULL);
    while(1);
    return 0;
}