// https://cs50.harvard.edu/x/2022/psets/1/credit/

#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Returns the nth digit of a number from right to left
int get_nth_digit(long number, int n);

int main(void)
{
    long int credit_card = get_long("Number: ");

    // Calculate the number of digits
    int digits = log10(credit_card) + 1;

    // Implementation of Luhn’s algorithm
    int odd_index_sum = 0, even_index_sum = 0;
    for (int i = 0; i < digits; i++)
    {
        int current_digit = get_nth_digit(credit_card, i + 1);

        if (i % 2 == 0)
        {
            even_index_sum += current_digit;
        }
        else
        {
            int digit_doubled = current_digit * 2;
            odd_index_sum += (digit_doubled / 10) + (digit_doubled % 10);
        }
    }
    bool valid_card = (even_index_sum + odd_index_sum) % 10 == 0;

    // Assigns the company that owns the credit card to 'company'
    string company = "INVALID";
    if (valid_card)
    {
        int first_digit = get_nth_digit(credit_card, digits);
        int second_digit = get_nth_digit(credit_card, digits - 1);

        if (digits == 13 && first_digit == 4)
        {
            company = "VISA";
        }
        else if (digits == 15 && first_digit == 3 && (second_digit == 4 || second_digit == 7))
        {
            company = "AMEX";
        }
        else if (digits == 16)
        {
            if (first_digit == 4)
            {
                company = "VISA";
            }
            else if (first_digit == 5 && second_digit >= 1 && second_digit <= 5)
            {
                company = "MASTERCARD";
            }
        }
    }

    // Prints 'company'
    printf("%s\n", company);
}

int get_nth_digit(long number, int n)
{
    return (number % (long)pow(10, n)) / pow(10, n - 1);
}
