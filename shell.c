char *tokenArray;
char *argumentList[10];

int main()
{
    for (int i = 0; i < 10; i++)
    {
        argumentList[i] = (char *)malloc(100 * sizeof(char));
    }
}