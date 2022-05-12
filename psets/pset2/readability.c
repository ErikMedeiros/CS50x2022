// https://cs50.harvard.edu/x/2022/psets/2/readability/

#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function prototype
int count_words(string text);
int count_letters(string text);
int count_sentences(string text);

int main(void)
{
    // Getting user input
    string text = get_string("Text: ");

    // Number of words
    int words = count_words(text);
    // Average of letters per 100 word
    float L = (count_letters(text) / (float) words) * 100;
    // Average of sentences per 100 word
    float S = (count_sentences(text) / (float) words) * 100;

    // Coleman-Liau index.
    int index = round(0.0588f * L - 0.296f * S - 15.8f);

    // Print grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_words(string text)
{
    int length = strlen(text), words = 1;

    for (int i = 0; i < length; i++)
    {
        if (isspace(text[i]) != 0)
        {
            words += 1;
        }
    }

    return words;
}

int count_letters(string text)
{
    int length = strlen(text), letters = 0;

    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            letters += 1;
        }
    }

    return letters;
}

int count_sentences(string text)
{
    int length = strlen(text), sentences = 0;

    for (int i = 0; i < length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences += 1;
        }
    }

    return sentences;
}
