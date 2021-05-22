#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LEN_LINE    100

int main(void)
{
    char command[MAX_LEN_LINE];
    char *args[] = {command, NULL};
    int ret, status;
    pid_t pid, cpid;
    
    while (true) {
        char *s;
        int len;
        
        printf("MyShell $ ");
        s = fgets(command, MAX_LEN_LINE, stdin);
        if (s == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(1);
        }
        
        len = strlen(command);
        printf("%d\n", len);
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0'; 
        }
        
        printf("[%s]\n", command);
      
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } 
        if (pid != 0) {  /* parent */
            cpid = waitpid(pid, &status, 0);
            if (cpid != pid) {
                fprintf(stderr, "waitpid failed\n");        
            }
            printf("Child process terminated\n");
            if (WIFEXITED(status)) {
                printf("Exit status is %d\n", WEXITSTATUS(status)); 
            }
        }
        else {  /* child */
            ret = execve(args[0], args, NULL);
            if (ret < 0) {
                fprintf(stderr, "execve failed\n");   
                return 1;
            }
        } 
    }
    return 0;
}
//ls
void 
ls(void)
{

char *path;
DIR *dp;

path = (argc==0)? "." : argv[0];

if((dp = opendir(path)) ==NULL) 
PRINT_ERR_RET();


if(optc==0) 
print_name(dp); 
else 
print_detail(dp,path); 
closedir(dp);
printf("\n"); 
}

//exit
int main()
{
    int pid;
    int status;
    int spid;
    pid = fork();

    if (pid == 0)
    {
        sleep(5);
        printf("I will be back %d\n", getpid());
        return 1;
    }

    else if(pid > 0)
    {
        printf("Im parent %d\n", getpid());
        printf("Press any key and wait\n");
        getchar();
        spid = wait(&status);
        printf("child process wait success \n");
        printf("PID         : %d\n", spid);
        printf("Exit Value  : %d\n", WEXITSTATUS(status));
        printf("Exit Stat   : %d\n", WIFEXITED(status));
    }
    else
    {
        perror("fork error :");
    }
}

//pwd
//#include <stdio.h>
//#include <unistd.h>
 
int main()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n",cwd);
    chdir("test_folder");
    getcwd(cwd, sizeof(cwd));
    printf("%s\n",cwd);
 
    return 0;
}
