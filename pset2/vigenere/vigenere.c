// vigenere.c by Michael Peer 2018
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
//Calculate ciphertext
void parse_plain(char *plain, char *k)
{
    int len = strlen(plain);
    int pos_k = 0;
    for (int x = 0; x < len; x++)
    {
        char c = plain[x];
        char c2 = ' ';
        int asc = c;
        //Only letters a-z and A-Z will be converted
        if ((asc >= 65 && asc <= 90) || (asc >= 97 && asc <= 122))
        {
            int asc_k = k[pos_k];
            //Take single character from k, convert to lowercase and number
            // Aa=0, Bb=1,...
            if (asc_k >= 97)
            {
                asc_k = asc_k - 32;
            }
            asc_k = asc_k - 65;
            //Loop through k
            pos_k++;
            if (pos_k == strlen(k))
            {
                pos_k = 0;
            }
            int asc2 = asc + asc_k;

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
//k is valid if len > 0 and only letters
bool k_is_valid(char *k)
{
    int len = strlen(k);
    bool is_valid = false;
    if (len == 0)
    {
        return false;
    }
    for (int x = 0; x < len; x++)
    {
        int asc = k[x];
        if ((asc >= 65 && asc <= 90) || (asc >= 97 && asc <= 122))
        {
            is_valid = true;
        }
        else
        {
            return false;
        }
    }
    return true;
}
int main(int argc, char *argv[])
{
    if (argc != 2 || !k_is_valid(argv[1]))
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    printf("plaintext:");
    char *plain = get_string();
    printf("ciphertext:");
    parse_plain(plain, argv[1]);
    printf("\n");
    return 0;
}