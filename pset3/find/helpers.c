/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <math.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

// binary search function
bool search(int value, int values[], int n)
{
    int min = 0;
    int max = n - 1;
    int midpt(int min, int max);
    while (value != values[midpt(min, max)])
    {
        if (max < min)
        {
            return (0);
        }
        else
        {
            if (value > values[midpt(min, max)])
            {
                min = midpt(min, max) + 1;
            }
            else if (value < values[midpt(min, max)])
            {
                max = midpt(min, max) - 1;
            }
        }
    }

    if (value == values[midpt(min, max)])
    {
        return (1);
    }
    return (0);
}

// midpoint function
int midpt(int min, int max)
{
    int mid;
    if ((max - min) % 2 == 0)
    {
        mid = ((max - min) / 2) + min;
    }
    else
    {
        mid = (int) floor((max - min) / 2) + min;
    }
    return mid;
}

/**
 * Sorts array of n values.
 */

void sort(int values[], int n)
{
    // Insertion sort: O(n^2) sorting algorithm
    int i, j, element;
    for (i = 1; i <= n - 1; i++)
    {
        element = values[i];
        j = i;
        while (j > 0 && values[j - 1] > element)
        {
            values[j] = values[j - 1];
            j = j - 1;
        }
        values[j] = element;
    }
    return;
}
