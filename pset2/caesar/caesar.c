// caesar.c by Michael Peer 2018
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
void parse_plain(char *plain, int k)
{
    int len = strlen(plain);
    for (int x = 0; x < len; x++)
    {
        char c = plain[x];
        char c2 = ' ';
        int asc = c;
        if ((asc >= 65 && asc <= 90) || (asc >= 97 && asc <= 122))
        {
            int asc2 = asc + k;
            if (asc <= 90 && asc2 > 90)
            {
                asc2 = (asc2 - 90) + 64;
            }
            if (asc <= 122 && asc2 > 122)
            {
                asc2 = (asc2 - 122) + 96;
            }
            c2 = asc2;
        }
        else
        {
            c2 = c;
        }
        printf("%c", c2);
    }
}
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    int k = atoi(argv[1]) % 26;
    printf("plaintext:");
    char *plain = get_string();
    printf("ciphertext:");
    parse_plain(plain, k);
    printf("\n");
    return 0;
}