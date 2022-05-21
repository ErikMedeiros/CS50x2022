// https://cs50.harvard.edu/x/2022/psets/5/speller/

// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 4096;

// Hash table
node *table[N];

// Words inside hash table
unsigned int table_size = 0;

// Functions prototypes
void replace(char *s, const char find, const char replace);
void insert(char *s);
void convert_to_lower(char *s);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Copy the word and make it lowercase
    char lower[strlen(word) + 1];
    strcpy(lower, word);
    convert_to_lower(lower);

    unsigned int code = hash(lower);
    node *current = table[code];

    while (current != NULL)
    {
        if (strcmp(lower, current->word) == 0)
        {
            return true;
        }

        current = current->next;
    }

    return false;
}

// Convert string to lowercase
void convert_to_lower(char *s)
{
    while (*s)
    {
        *s = tolower(*s);
        s++;
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int length = strlen(word);
    unsigned int code = 0;

    for (int i = 0; i < length; i++)
    {
        code += (i + 2) * tolower(word[i]);
    }

    return code % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        fclose(dict);
        return false;
    }

    // Initialize table to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char word[LENGTH + 1];
    while (!feof(dict))
    {
        if (fgets(word, LENGTH + 1, dict) != NULL)
        {
            replace(word, '\n', '\0');

            if (strlen(word) > 0)
            {
                insert(word);
                table_size += 1;
            }
        }
    }

    fclose(dict);
    return true;
}

// Find and replace char inside string
void replace(char *s, const char find, const char replace)
{
    int index = 0;
    bool replaced = false;

    do
    {
        if (s[index] == find)
        {
            s[index] = replace;
            replaced = true;
        }

        index += 1;
    }
    while (index < LENGTH + 1 && !replaced);
}

// Insert word into hash table
void insert(char *s)
{
    unsigned int code = hash(s);

    node *temp = malloc(sizeof(node));
    strcpy(temp->word, s);
    temp->next = NULL;

    node *current = table[code];

    if (current != NULL)
    {
        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = temp;
    }
    else
    {
        table[code] = temp;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return table_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    if (table_size == 0)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        node *current = table[i];

        while (current != NULL)
        {
            node *next = current->next;
            free(current);
            current = next;
        }
    }

    return true;
}
