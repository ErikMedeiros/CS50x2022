// https://cs50.harvard.edu/x/2022/psets/1/mario/more/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Keep asking for input if it isn't inside the bounds
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // loops throught the rows
    for (int i = 1; i <= height; i++)
    {
        for (int j = height - i; j > 0; j--)
        {
            printf(" ");
        }

        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        // space between pyramids
        printf("  ");

        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
