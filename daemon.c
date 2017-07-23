#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char **argv)
{
    pid_t pid,sid;
    FILE *fp= NULL;
    int i;
    pid = fork();// fork a new child process, returns 0 if successfully forked

    if (pid < 0)
    {
        printf("fork failed!\n");
        exit(1);
    }

    if (pid > 0)// its the parent process
    {
       printf("pid of child process %d \n", pid);
        exit(0); //terminate the parent process succesfully
    }

    umask(0);//unmasking the file mode

    sid = setsid();//set new session
    if(sid < 0)
    {
        exit(1);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO); // closing all the file descriptors like stdin,stdout and stderr
    close(STDERR_FILENO);

    fp = fopen ("mydaemonfile.txt", "w+");
    while (i < 10)
    {
        sleep(1);
        fprintf(fp, "%d", i);
        i++;
    }
    fclose(fp);
  
    return 0;
}
