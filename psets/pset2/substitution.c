// https://cs50.harvard.edu/x/2022/psets/2/substitution/

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Key's number of characters
const int KEY_SIZE = 26;

string encrypt(string plaintext, string key);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // Exit with error if invalid key size
        if (strlen(argv[1]) != KEY_SIZE)
        {
            printf("Key must contain only %i characters.\n", KEY_SIZE);
            return 1;
        }

        for (int i = 0; i < KEY_SIZE; i++)
        {
            // Exit with error if key contains invalid character
            if (isalpha(argv[1][i]) == 0)
            {
                printf("Key must contain only letters.\n");
                return 1;
            }

            if (i < KEY_SIZE - 2)
            {
                // Exit with error if key contains duplicate characters
                char *next_occurrence = strchr(argv[1] + i + 1, argv[1][i]);
                if (next_occurrence != NULL)
                {
                    printf("Key must not contain repeated letters.\n");
                    return 1;
                }
            }
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    string ciphertext = encrypt(plaintext, argv[1]);
    printf("ciphertext: %s\n", ciphertext);

    // Free memory
    free(ciphertext);
    return 0;
}

string encrypt(string plaintext, string key)
{
    int length = strlen(plaintext);
    // Allocate enough memory
    string ciphertext = malloc(length * sizeof(char));

    for (int i = 0; i < length; i++)
    {
        char current_char = plaintext[i];
        char encrypted_char = current_char;

        if (isalpha(current_char) != 0)
        {
            bool lower = islower(current_char) != 0;
            int key_code = lower ? 97 : 65;
            int index = (int)current_char - key_code;

            encrypted_char = lower ? tolower(key[index]) : toupper(key[index]);
        }

        // Concat encrypted character to string
        strncat(ciphertext, &encrypted_char, 1);
    }

    return ciphertext;
}
