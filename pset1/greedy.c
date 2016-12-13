/**
 * greedy.c
 * 
 * Ben Love
 * benuklove@gmail.com
 * 
 * This program asks users for the amount of change due.
 * It then calculates the least number of coins to give back.
 */

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{

    // asks user the amount of change owed and validates positive float
    float change;
    do
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
    while (change < 0);
    
    // rounding the change here, hopefully without simply truncating
    double pennies;
    pennies = round(change * 100);
    
    // cast double as int
    int cents = pennies;
    
    // making change: this section stores coin totals from largest (quarter)
    // to smallest (penny) then sums all coins for output
      
    // quarters
    int q = cents / 25 - ((cents % 25) / 25);
    // dimes
    int d = (cents - q * 25) / 10 - (((cents - q * 25) % 10) / 10);
    // nickels
    int n = (cents - q * 25 - d * 10) / 5
            - (((cents - q * 25 - d * 10) % 5) / 5);
    // pennies
    int p = (cents - q * 25 - d * 10 - n * 5);
    // total coins
    int total = q + d + n + p;
    printf("%d\n", total);
        
}

