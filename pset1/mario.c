/**
 * mario.c
 * 
 * Ben Love
 * benuklove@gmail.com
 * 
 * Prints a set of right-justified stairs represented with #.
 * User input for the height.
 * Height must be non-negative integer.
 */
 
#include <cs50.h>
#include <stdio.h>

int main(void)
{
// user input for height with range validation
    int height;
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);

// corner case of zero stair height using if-else
    if (height == 0)
    {
        return(0);
    }
    else
    {    
// main print section with outside 'for loop' to loop through stair level
// n is the row number
// i is the number of spaces on the row
// j is the number of hashes on the row

        for(int n = 1; n <= height; n++)
        {
// inside 'for loops' to loop through spaces then hashes
            int i;
            for(i = 1; i <= height - n; i++)
            {
                printf(" ");
            }
            int j;
            for(j = 1; j <= n + 1; j++)
            {
                printf("#");
            }
            printf("\n");    
        }
    }
}

