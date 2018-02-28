//crack.c by Michael Peer 2018
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void stringbuilder(char *f2, char *hash, int d, int max)
{
    //65 90 97 122
    for (int x = 0; x <= 51; x++)
    {
        int asc = 65 + x;
        char c = ' ';
        if (asc > 90)
        {
            asc = asc + 6;

        }
        c = asc;
        f2[d - 1] = c;
        if (d >= 3)
        {
            f2[d] = '\0';
            char salt[2] = "";
            salt[0] = f2[0];
            salt[1] = f2[1];
            char *enc = crypt(f2, salt);
            int res = strcmp(enc, hash);
            if (res == 0)
            {
                printf("%s\n", f2);

            }

        }
        if (d < max)
        {
            stringbuilder(f2, hash, d + 1, max);

        }

    }
}
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    char tmp[5];
    //Check for password with 3-4 characters
    stringbuilder(tmp, argv[1], 1, 4);
    return 0;
}
