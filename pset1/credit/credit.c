//credit.c Michael Peer 2018
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Calculate length of fgets buffer
int get_len(char *s)
{
    int len = 0;
    for (int x = 0; x < 20; x++)
    {
        if (s[x] != '\0')
        {
            len++;

        }
    }
    return len - 1;
}
//Check if syntax is valid and return card type
int get_cardtype(char *s, int len)
{
    char c = s[0];
    char c2 = s[1];
    if (c == '4' && len == 16)
    {
        return 1; //VISA
    }
    else if (c  == '3' && len == 15 && (c2  == '4' || c2 == '7'))
    {
        return 2; //AMEX
    }
    else if (c == '5' && len == 16 && (c2 == '1' || c2 == '2' || c2 == '3' || c2 == '4' || c2 == '5'))
    {
        return 3; //MASTERCARD
    }
    return 0;
}
//Calculate checksum and determine validity
int calc(char *inp, int len)
{
    int parity = len % 2;
    int sum = 0;
    int digit = 0;
    for (int x = (len - 1); x >= 0; x--)
    {
        digit = inp[x] - 48;
        if (parity == x % 2)
        {
            digit = digit * 2;
        }
        sum += digit / 10;
        sum += digit % 10;
    }
    return sum % 10;
}
void read_inp()
{
    const char *card_type[] = {"INVALID", "VISA", "AMEX", "MASTERCARD"};
    while (1)
    {
        printf("Number: ");
        char buf[20] = "";
        fflush(stdin);
        fgets(buf, sizeof(buf), stdin);
        int len = get_len(buf);
        int ind_card_type = 0;
        int valid_checksum = 0;
        ind_card_type = get_cardtype(buf, len);
        if (ind_card_type > 0 && len > 0)
        {
            valid_checksum = calc(buf, len);
            if (valid_checksum == 0)
            {
                printf("%s\n", card_type[ind_card_type]);
                break;

            }
            else if (len > 0)
            {
                printf("%s\n", "INVALID");
                break;

            }


        }
        else
        {
            printf("INVALID\n");
            break;
        }

    }
}

int main(void)
{
    read_inp();
}
