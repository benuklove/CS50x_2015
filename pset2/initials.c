/**
 * initials.c
 * 
 * Ben Love
 * benuklove@gmail.com
 * 
 * This C program takes user input as a string (ie their name),
 * and returns a capital first letter of each word (ie thier initials).
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string s = GetString();
    // check that something is entered
    if (s != NULL)
    {
        // capitalize the first letter
        if (s[0] >= 'a' && s[0] <= 'z')
        {
            printf("%c", s[0] - ('a' - 'A'));
        }
        else
        {
            printf("%c", s[0]);
        }
        // capitalize operation on remaining words (names)        
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            // capitalize the letter after any space
            if (s[i] == ' ')
            {
                if (s[i + 1] >= 'a' && s[i + 1] <= 'z')
                {
                    printf("%c", s[i + 1] - ('a' - 'A'));
                }
                else
                {
                    printf("%c", s[i + 1]);
                }
            }
        }
    }
    printf("\n");
}
