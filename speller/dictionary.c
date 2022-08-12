// Implements a dictionary's functionality

#include <ctype.h>       // toupper
#include <stdbool.h>     // bool
#include <stdlib.h>      // malloc; free
#include <stdio.h>       // printf; fopen; fclose; fscanf
#include <string.h>      // strcpy
#include <strings.h>     // strcasecmp

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Word count
unsigned int word_count = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 150000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // индексирует в хэш слово и выдает тот же хэш
    int hash_index  = hash(word);
    node *cursor = table[hash_index];

    while (cursor != NULL)
    {
        // Compare words
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long sum = 0;
    for (int j = 0; j < strlen(word); j++)
    {
        sum += tolower(word[j]);
    }
    return sum % N ;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Declare variable
    char buffer_word[LENGTH + 1];

    // Read string from file one at a time
    while (fscanf(file, "%s", buffer_word) != EOF)
    {
        // Create a new node for each word
        node *cursor = malloc(sizeof(node));
        if (cursor == NULL)
        {
            return false;
        }

        // Copy word into node
        strcpy(cursor->word, buffer_word);

        // Hash word to obtain a hash value
        int hash_index = hash(buffer_word);

        // Insert node into hash table at that location
        cursor->next = table[hash_index]; // cursor установили на текущий head
        table[hash_index] = cursor; // a head на новый список cursor

        // считаем количество word
        word_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_count > 0)
    {
        return word_count;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        if (table[i] == NULL)
        {
            return true;
        }
    }

    return false;
}
