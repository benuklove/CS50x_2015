/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Ben Love
 * benuklove@gmail.com
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// 26 letters of alphabet plus apostrophe
#define ARRAYSIZE 27

/**
 * Trie data structure, each cell with two components:
 * a boolean flag for end of word, and a pointer to next letter
 */
 
typedef struct node
{
    bool is_word;
    struct node* children[ARRAYSIZE];
}
node;
node *root;    

/**
 * Returns true if word is in dictionary else false.
 */

// convert letters from text to all lowercase
int lower(char alpha)
{
    if (isupper(alpha))
    {
        alpha = alpha + 32;
    }
    return alpha;
}

bool check(const char* word)
{
    node *cursor = root;
    int i = 1;
    
    // Loop to iterate-match each word from text to dictionary word
    while (word[i])
    {
        int alpha = lower(word[i]);
        if (cursor -> children[alpha - 97])
        {
            cursor = cursor -> children[alpha - 97];
            i++;
        }
        else
        {
            return false;
        }
        
    // Once each text word is matched by character, check if in dictionary
    }
    if (cursor -> is_word)
    {
        return true;
    }
    if (cursor -> is_word == false)
    {
        return false;
    }
    return true;
}

// used in functions "load" and "size" to track words loaded from dictionary
int wordcount = 0;

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Open dictionary and check that it's open
    FILE *file = fopen(dictionary, "r");
    if (file == false)
    {
        return false;
    }

    // Allocate memory for root node    
    root = calloc(ARRAYSIZE, sizeof(node));
    
    // Loop to load each character from dictionary into trie
    int c;
    while (fgetc(file) != EOF)
    {
        node *cursor = root;
        for (c = fgetc(file); c != '\n'; c = fgetc(file))
        {
            if (cursor -> children[c - 97] == false)
            {
                cursor -> children[c - 97] = calloc(1, sizeof(node));
            }
            cursor = cursor -> children[c - 97];
        }
        cursor -> is_word = true;
        wordcount++;

    }
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (wordcount != 0)
    {
        return wordcount;
    }
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
 void freetrie(node *cursor)
{
    for (int i = 0; i < 27; i++)
    {
        if (cursor -> children[i])
        {
            freetrie(cursor -> children[i]);
        }
    }
    free(cursor);
}

bool unload(void)
{
    // Uses recursive function, freetrie, to free allocated nodes
    freetrie(root);
    return true;
}


