//https://cs50.harvard.edu/x/2022/psets/1/hello/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask for a name and then say hello.
    string name = get_string("What's your name? ");
    printf("Hello, %s!\n", name);
}