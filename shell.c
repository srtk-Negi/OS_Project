#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *tokenArray;
char *argumentList[10];

int main()
{
    while (1)
    {
        int i = 0;
        for (i = 0; i < 10; i++)
        {
            argumentList[i] = (char *)malloc(sizeof(char) * 81);
            argumentList[i] = NULL;
        }

        printf("\033[0;31mshell$ ");
        printf("\033[0m");

        char str[1000];
        if (fgets(str, 1000, stdin))
        {

            tokenArray = strtok(str, " \n");

            i = 0;

            while (tokenArray != NULL)
            {
                if (i == 0)
                {
                    char *command = strdup(tokenArray);
                }

                argumentList[i] = strdup(tokenArray);
                tokenArray = strtok(NULL, " \n");
                i++;
            }

            for (i = 0; i < 10; i++)
            {
                if (argumentList[i] != NULL)
                {
                    printf("%s\n", argumentList[i]);
                }
            }
        }

        if (strncmp(str, "exit", 4) == 0)
        {
            printf("Exiting shell\n");
            break;
        }
    }
}