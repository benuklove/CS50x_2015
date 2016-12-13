/**
 * caesar.c
 * 
 * Ben Love
 * benuklove@gmail.com
 * 
 * This C program takes two arguments (the filename and a numeric "key").
 * It then takes a statement from the user and shifts the letters by
 * the key, with wrapping, providing a cipher known as the Caesar cipher.
 */
 
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
 
int main(int argc, string argv[])
{
    // this conditional block requires exactly two arguments
    if (argc != 2)
    {
        printf("Try again\n");
        return(1);
    }
    else
    {
        // convert the key from string to int and gets user text
        int key = atoi(argv[1]);
        if (key < 0)
        {
            printf("Try again\n");
            return(1);
        }
        string p = GetString();
        
        // for each character in the plain text, cast upper- or
        // lowercase ascii to int, then to alphabetic index (1-26),
        // shift with key, and output new cipher characters
        for (int i = 0, n = strlen(p); i < n; i++)
        {
            if (isupper(p[i]))
            {
                printf("%c", ((((int) p[i]) - 64) + key) % 26 + 64);
            }
            else if (islower(p[i]))
            {
                printf("%c", ((((int) p[i]) - 96) + key) % 26 + 96);
            }
            else
            {
                printf("%c", p[i]);
            }
        }
        printf("\n");    
    }    
    return(0);
}
