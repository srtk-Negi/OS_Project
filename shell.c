#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *tokenArr; // token array
char *argumentList[10];
int i = 0;

void chgDir(char *path, char *currDir)
{
    if (chdir(path) == -1)
    {
        printf("Error: Cannot change directory\n");
        return;
    }
    if ((getcwd(currDir, 1000)) == NULL)
    {
        perror("getcwd() error");
    }
    setenv("PWD", currDir, 1);
}

void showpid(int idList[])
{
    for (i = 0; i < 5; i++)
    {
        printf("%d\n", idList[i]);
    }
    return;
}
int main()
{
    char currDir[1000];
    if ((getcwd(currDir, 1000)) == NULL)
    {
    }
    while (1)
    {
        for (i = 0; i < 10; i++) // Malloc a char* pointer with longth of 81 and initialize it to NULL

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
            // Do coding as needed
        }
        tokenArr = strtok(str, "");
        i = 0;
        while (tokenArr != NULL)
        {
            if (i == 0)
            {
                char *command; // Declare the 'command' variable
                command = strdup(tokenArr);
            }
            argumentList[i] = strdup(tokenArr);
            tokenArr = strtok(NULL, " ");
            i++;
        }
        char *command; // Declare the 'command' variable
        if (strcmp(command, "cd") == 0)
        {
            chgDir(argumentList[1], currDir);
        }
        else if (strcmp(command, "showpid") == 0)
        {
            int idList[5] = {1, 2, 3, 4, 5};
            showpid(idList);
        }
        else
        {
            // Parent Process code goes here
        }
        if ((pid = fork()) == 0)
        {
            int execStatus;
            execStatus = execvp(command, argumentList);
            if (execStatus == -1)
            {
                printf("Error: Command not could not be executed\n");
                exit(1);
            }
            kill(pid, SIGTERM);
        }
        else
        {
            // Parent process  (your shell program itself)
            int status; // Declare the 'status' variable
            waitpid(pid, &status, 0);
        }
        if (strncmp(str, "exit", 4) == 0)
        {
            printf("EXITING!\n");
            break;
        }
        // Do something with input
    }
}