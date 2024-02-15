#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void performExit()
{
    printf("EXITING!\n");
    exit(0);
}

void showpid()
{
    printf("SHOWPID!\n");
}

void changeDirectory()
{
    printf("CHANGING DIRECTORY!\n");
}

int main()
{
    char *tokenArr;
    char *argumentList[10];
    char *command;
    int i;

    while (1)
    {
        for (i = 0; i < 10; i++)

        {
            argumentList[i] = (char *)malloc(sizeof(char) * 81);
            argumentList[i] = NULL;
        }

        printf("\033[0;31mshell$ ");
        printf("\033[0m");

        char str[1000];

        if (fgets(str, 1000, stdin) != NULL)
        {
            tokenArr = strtok(str, " ");
            i = 0;
            while (tokenArr != NULL)
            {
                if (i == 0)
                {
                    command = strdup(tokenArr);
                }
                argumentList[i] = strdup(tokenArr);
                tokenArr = strtok(NULL, " ");
                i++;
            }
        }
        if (strncmp(command, "exit", 4) == 0)
        {
            performExit();
        }
        else if (strncmp(command, "showpid", 7) == 0)
        {
            showpid();
        }
        else if (strncmp(command, "cd", 2) == 0)
        {
            changeDirectory();
        }
        else
        {
            pid_t pid = fork();
            if (pid < 0)
            {
                perror("fork");
                exit(1);
            }
            else if (pid == 0)
            {
                if (execvp(command, argumentList) < 0)
                {
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                int status;
                if (waitpid(pid, &status, 0) < 0)
                {
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}
