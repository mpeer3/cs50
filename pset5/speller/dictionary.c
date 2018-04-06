// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"

int dict_words = 0;

//MP: Each dictionary entry can be accessed via hash/index
//Single words are stored in a nested array to handle collisions.
typedef struct aword
{
    char aword[LENGTH + 1][20];
    int ct;
} aword;

aword words_dict[MAXDICT];
int words_count = 0;

//MP: Calculate hash
int calc_hash(char *s)
{
    unsigned int res = 0;
    for (int ct = 0, n = strlen(s); ct < n; ct++)
    {

        res = res * 97 + s[ct];
    }


    return res % MAXDICT;

}
//MP: Perform check with a given word
bool check(char *word)
{
    int l =  strlen(word);
    char w[l + 1];
    //MP: Convert input to lowercase
    for (int pos = 0 ; pos < l; pos++)
    {
        w[pos] = tolower(word[pos]);
    }
    w[l] = '\0';
    words_count = words_count + 1;
    //MP: Calculate hash and search word at indes in subarray
    int ind = calc_hash(w);
    for (int x = 0; x < words_dict[ind].ct; x++)
    {
        if (strcmp(words_dict[ind].aword[x], w) == 0)
        {
            return true;

        }
    }
    return false;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    char dict_word[LENGTH + 1];
    //Initialize dictionary array
    for (int x = 0; x < MAXDICT; x++)
    {
        words_dict[x].ct = 0;
    }

    FILE *d = fopen(dictionary, "r");
    if (d == NULL)
    {
        return false;
    }
    //MP: Loop through dictionary and calculate hash/index.
    //Add dictionary value to array at index
    while (fscanf(d, "%s", dict_word) != EOF)
    {
        int ind = calc_hash(dict_word);
        int pos = words_dict[ind].ct;
        strcpy(words_dict[ind].aword[pos], dict_word);
        words_dict[ind].ct++;
        dict_words++;

    }
    fclose(d);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return dict_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //MP: Not needed since malloc not used.
    return true;
}
