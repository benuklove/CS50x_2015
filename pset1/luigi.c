/** 
 * temp file for manipulating mario.c
 * also, not the final - doing some cleanup
 */
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
    printf("Height: ");
    h = GetInt();
    printf("The number you gave me was %d.\n", h);
    }
    while (h < 0 || h > 23);
// n is the row number
// i is the number of spaces on the row
// j is the number of hashes
    if (h == 0)
    {
        printf("\n");
    }
    else
    {    
        for(int n = 1; n <= h; n++)
        {
            int i;
            for(i = 1; i <= h-n; i++)
            {
                printf(" ");
            }
            int j;
            for(j = 1; j <= n+1; j++)
            {
                printf("#");
            }
            printf("\n");    
        }
    }
}



