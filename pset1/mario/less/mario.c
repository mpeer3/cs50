//Mario (less comfortable) by Michael Peer 2018
#include <stdio.h>
//Printing character ch count times
void rep(char ch, int count)
{
    if (count > 0)
    {
        for (int x = 1; x <= count; x++)
        {
            printf("%c", ch);
        }
    }
}
//Print pyramid
void printit(int mx)
{
    int max = mx + 1;
    for (int x = 2; x <= max; x++)
    {
        rep(' ', max - x);
        rep('#', x);
        printf("\n");
    }
}
//Read and validate input from stdin
void read_inp()
{
    while (1)
    {
        char inp[10];
        int max = 0;
        int res = 0;
        fflush(stdin);
        fgets(inp, sizeof(inp), stdin);
        res = sscanf(inp, "%d", &max);
        if (res == 1 && max > 0 && max < 24)
        {
            printit(max);
            break;
        }
        else if (res == 1 && max == 0)
        {
            break;
        }
        else
        {
            printf("Height:");
        }
    }
}

//Entry point
int main(void)
{
    printf("Height:");
    read_inp();
}

