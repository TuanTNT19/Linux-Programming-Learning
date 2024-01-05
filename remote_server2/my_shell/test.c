#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

int main() {
    // Example: Get the value of the "HOME" environment variable
    char *name = readline("\n>> ");
	printf("%s\n",name);

    return 0;
}