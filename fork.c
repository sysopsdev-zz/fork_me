#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int pid;
    pid = fork();

    if(pid == 0) 
    {
        printf("%d\n%d\n", getpid(), getppid());
        sleep(5);
    }
    else
    {
        wait(NULL);
        printf("%d\n%d\n", getpid(), pid);
    }
    return 0;
}
