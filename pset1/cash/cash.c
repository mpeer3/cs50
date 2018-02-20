//cash.c solution by Michael Peer 2018
#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
    while (1)
    {

        int sum = 0;
        float inp = round(get_float("Change owed: ") * 100);
        int inp100 = inp;
        if (inp > 0)
        {
            sum = inp100 / 25;
            inp100 = inp100 % 25;
            sum += inp100 / 10;
            inp100 = inp100 % 10;
            sum += inp100 / 5;
            sum += inp100 % 5;
            printf("%d\n", sum);
            break;

        }
    }



}