// Helper functions for music

#include <cs50.h>

#include "helpers.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    if (fraction == NULL)
    {
        return 0;
    }
    int len = fraction[0] - 48;
    if (fraction[2] == '4')
    {
        len = len * 2;
    }
    if (fraction[2] == '2')
    {
        len = len * 4;
    }
    return len;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO
    if (note == NULL)
    {
        return 0;
    }
    int len = strlen(note);
    int pitch = note[len - 1] - 48;
    int pitch_rel = pitch - 4;
    int pitch_shift = pitch_rel * 12;
    char keys[] = "CDEFGAB";
    char key = note[0];
    int arr_shift[7] = {-9, -7, -5, -4, -2, 0, 2};
    int shift = 0;
    for (int ct = 0; ct < 7; ct++)
    {
        if (key == keys[ct])
        {
            shift = arr_shift[ct];
        }
    }
    if (note[1] == '#')
    {
        shift++;
    }
    if (note[1] == 'b')
    {
        shift--;
    }
    shift = shift + pitch_shift;
    double exp = shift / 12.0;
    double freq = round(pow(2, exp) * 440);
    int res = freq;
    return res;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{

    if (s == NULL)
    {
        return false;
    }
    int len = strlen(s);
    if (len == 0)
    {
        return true;
    }
    return false;
}
