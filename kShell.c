#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

char *tokenArr;
char *argumentList[10];
int a = 0;
int idList[5];

void chgDir(char *path, char *currDir){
    if (chdir(path) == -1)
    {
        printf("Error: Cannot change directory\n");
        return;
    }
    if ((getcwd(currDir, 1000)) == NULL)
    {
        perror("getcwd() error");
    }
    setenv("pwd", currDir, 1);
}
void showpid(int idList[]){
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", idList[i]);
    }
    return;
}

int main()
{
    char currDir[1000];
    int status;
    pid_t pid;
    int execStatus;
    int i;

    while (1)
    {
        for (i = 0; i < 10; i++)
        {
            argumentList[i] = (char *)malloc(sizeof(char) * 81);
            argumentList[i] = NULL;
        }
        // Get user input using fgets
        printf("\033[0;31mshell$ ");
        printf("\033[0m");

        char str[1000];
        if (fgets(str, 1000, stdin) != NULL)
        {
            tokenArr = strtok(str, " ");
            int i = 0;
            char *command = NULL;
            while (tokenArr != NULL && i < 10)
            {
                if (i == 0)
                {
                    command = strdup(tokenArr);
                }
                argumentList[i] = strdup(tokenArr);
                tokenArr = strtok(NULL, " ");
                i++;
            }
            if (command != NULL)
            {
                if (strcmp(command, "cd") == 0)
                {
                    chgDir((argumentList[1]), currDir);
                }
                else if (strcmp(command, "showpid") == 0)
                {
                    showpid(idList);
                }else{
                    // Child process code does here
                    if ((pid = fork()) == 0)
                    {
                        execStatus = execvp(command, argumentList);
                        if (execStatus == -1)
                        {
                            printf("Error: Command could not be executed\n");
                            exit(1);
                        }
                        kill(pid, SIGTERM);
                    }
                    else{
                        if(a == 5){
                            a = 0;
                        }
                        idList[a] = pid;
                        a++;
                        waitpid(pid, &status, 0);
                    }
                }
            }
            if (strncmp(str, "exit", 4) == 0)
            {
                printf("EXITING\n");
                break;
            }
        }
    }
    return 0;
}