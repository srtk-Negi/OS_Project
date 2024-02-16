#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void chgDir(char *path, char *currDir);
void showpid(int idList[]);

int main()
{
    pid_t pid;
    int i = 0;
    int a = 0; // track idList
    int tokenCount = 0;
    int *status = 0;
    int execStatus = 0;
    int idList[5] = {0, 0, 0, 0, 0};
    int argc = 0; // Keep track of # of arguments
    char str[1000] = "";
    char *command = "";
    char *tokenArr; // token array
    char *argumentList[10];
    char currDir[1000];

    for (i = 0; i < 10; i++) // Malloc a char* pointer with length 81 and initialize it to null
    {
        argumentList[i] = (char *)malloc(sizeof(char) * 81);
        argumentList[i] = NULL;
    }

    if ((getcwd(currDir, 1000)) == NULL)
    {
        perror("getcwd() error");
    }

    while (1)
    {
        // Get user input using fgets
        printf("\033[0;31m%s$ ", currDir);
        printf("\033[0m"); // Reset from red
        if (fgets(str, 1000, stdin) != NULL)
        {
            char *p;
            // check exist newline
            p = strchr(str, '\n');
            if (p != NULL)
            {
                *p = 0;
            }
            else
            {
                // clear upto newline
                scanf("%*[^\n]");
                scanf("%*c");
            }
        }

        // Remove the '\n' character from fgets
        for (i = 0; i < strlen(str); i++)
        {
            if (str[i] == '\n')
            {
                str[i] = '\0';
                break;
            }
        }

        if (strncmp(str, "exit", 4) == 0)
        {
            printf("EXITING!\n");
            break;
        }

        // Using strtok to create tokens and count each token as one word
        tokenArr = strtok(str, " ");
        /*
        while(tokenArr != NULL)
        {
            printf("token is: %s\n", tokenArr);
            tokenCount++;
            tokenArr = strtok(NULL, " ");
        }

        printf("Number of words: %d\n", tokenCount);
        */

        i = 0;
        while (tokenArr != NULL)
        {
            if (i == 0)
            {
                command = strdup(tokenArr);
            }
            argumentList[i] = strdup(tokenArr);
            argc++;
            tokenCount++;
            tokenArr = strtok(NULL, " ");
            i++;
        }

        if (strcmp(command, "cd") == 0)
        {
            chgDir(argumentList[1], currDir);
        }
        else if (strcmp(command, "showpid") == 0)
        {
            showpid(idList);
        }
        else
        {
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
            else
            {
                if (a == 5)
                {
                    a = 0;
                }
                idList[a] = pid;
                a++;
                waitpid(pid, status, 0);
            }
        }

        // Reset variables
        for (i = 0; i < argc; i++)
        {
            argumentList[i] = NULL;
        }

        tokenCount = 0;
        argc = 0;
    }

    // Free argumentList pointers
    for (i = 0; i < argc; i++)
    {
        free(argumentList[i]);
    }

    return 0;
}

void chgDir(char *path, char *currDir)
{
    if (chdir(path) == -1)
    {
        printf("Error: cannot change directory\n");
        return;
    }
    if ((getcwd(currDir, 1000)) == NULL)
    {
        perror("getcwd() error");
    }
    setenv("pwd", currDir, 1);
}

void showpid(int idList[])
{
    int i = 0;
    for (i = 0; i < 5; i++)
    {
        printf("%d\n", idList[i]);
    }
    return;
}