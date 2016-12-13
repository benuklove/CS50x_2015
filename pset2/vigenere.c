/**
 * vigenere.c
 * 
 * Ben Love
 * benuklove@gmail.com
 * 
 * This C program takes two arguments (the filename and an alpha "key").
 * It then takes a statement from the user and shifts the letters by
 * the key, with wrapping, providing a cipher known as Vigenere.
 */
 
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int keyalphacheck(string argument);
int alphacount(int i, string p);
int addkey(int alphacount, string key, string p);

int main(int argc, string argv[])
{
    // this conditional block requires exactly two arguments
    if (argc != 2)
    {
        printf("Try again\n");
        return(1);
    }
    // uses a function, keyalphacheck to make sure the key is all letters
    else if ((keyalphacheck (argv[1])) == 1)
    {
        printf("Try again\n");
        return(1);
    }
    // main iteration segment
    else
    {
        // convert the key from string to int and gets user text
        string key = argv[1];
        string p = GetString();
        
        // for each character in the plain text, cast upper- or
        // lowercase ascii to int, then to alphabetic index (1-26),
        // shift with appropriate character of key, output cipher characters
        for (int i = 0, n = strlen(p); i < n; i++)
        {
            // main calculations - calling functions addkey and alphacount
            int uppertemp = ((((int) p[i]) - 64) 
                            + addkey(alphacount(i, p), key, p)) % 26;
            int lowertemp = ((((int) p[i]) - 96)
                            + addkey(alphacount(i, p), key, p)) % 26;
            
            if (isalpha(p[i]))
            {
                if (isupper(p[i]))
                {
                    // special case fix for 'Z'
                    if (uppertemp == 0)
                    {
                        printf("%c", 90);
                    }
                    else
                    {
                        printf("%c", uppertemp + 64);
                    }
                }
                else if (islower(p[i]))
                {
                    // special case fix for 'z'
                    if (lowertemp == 0)
                    {
                        printf("%c", 122);
                    }
                    else
                    {
                        printf("%c", lowertemp + 96);
                    }
                }
                else
                {
                    printf("%c", p[i]);
                }
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
// end of main function

// function to keep track of how many alpha characters are in the plain text
// this is used to iterate through the key accurately
int alphacount(int i, string p)
{
    int j;
    int count = 0;
    for (j = 0; j <= i; j++)
    {
        if (isalpha(p[j]))
        {
            count = count + 1;
        }
        else
            ;
    }
    return count;
}

// function to determine how far to shift alpha-indexed plain text
// A or a is 0 and Z or z is 25
int addkey(int alphacount, string key, string p)
{
    int shift = 0;
    int len = strlen(key);
    int k = (alphacount + len - 1) % len;
    if (isupper(key[k]))
    {
        shift = (int) key[k] - 65;
    }
    else if (islower(key[k]))
    {
        shift = (int) key[k] - 97;
    }
    else
        ;
    return shift;
}

// function to make sure all characters of the key are alphabetic
int keyalphacheck(string argument)
{
    int i, n, check;
    string key1 = argument;
    for (i = 0, n = strlen(key1); i < n; i++)
    {
        if (isalpha(key1[i]))
        {
            check = 0;
        }
        else
        {
            check = 1;
        }
    }
    return check;
    }
