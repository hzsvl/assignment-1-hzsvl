// credit.c
// CS50x - Week 1, Problem Set 1
//
// Exercise: Credit Card Validator
// ------------------------------------------
// Validate a credit card number using Luhn's Algorithm,
// then identify whether it is AMEX, MASTERCARD, VISA, or INVALID.
//
// How to compile:  make credit
// How to run:      ./credit
// How to check:    check50 cs50/problems/2024/x/credit

#include <cs50.h>
#include <stdio.h>

// Luhn's Algorithm (overview)
// ------------------------------------------------------------
// 1. Starting from the SECOND-TO-LAST digit, multiply every other digit by 2.
// 2. If any product >= 10, add its digits together.
// 3. Sum all doubled digits -> sum_doubled
// 4. Sum all other digits -> sum_rest
// 5. If (sum_doubled + sum_rest) % 10 == 0 => VALID

int main(void)
{
    // TODO: Prompt user for a credit card number using get_long()
    long number = get_long("Number: ");

    // ------------------------------------------------------------
    // STEP 1: Count the number of digits
    // ------------------------------------------------------------
    int length = 0;
    long temp = number;

    while (temp > 0)
    {
        temp /= 10;
        length++;
    }

    // ------------------------------------------------------------
    // STEP 2: Apply Luhn's Algorithm
    // ------------------------------------------------------------
    int sum_doubled = 0;
    int sum_rest = 0;

    int position = 0;
    temp = number;

    while (temp > 0)
    {
        int digit = temp % 10;

        if (position % 2 == 1)
        {
            int doubled = digit * 2;
            if (doubled >= 10)
            {
                sum_doubled += (doubled / 10) + (doubled % 10);
            }
            else
            {
                sum_doubled += doubled;
            }
        }
        else
        {
            sum_rest += digit;
        }

        temp /= 10;
        position++;
    }

    // ------------------------------------------------------------
    // STEP 3: Check validity
    // ------------------------------------------------------------
    if ((sum_doubled + sum_rest) % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // ------------------------------------------------------------
    // STEP 4: Identify card type
    // ------------------------------------------------------------
    long first_two = number;
    while (first_two >= 100)
    {
        first_two /= 10;
    }

    int first_digit = first_two / 10;

    // AMEX
    if (length == 15 && (first_two == 34 || first_two == 37))
    {
        printf("AMEX\n");
    }
    // MASTERCARD
    else if (length == 16 && (first_two >= 51 && first_two <= 55))
    {
        printf("MASTERCARD\n");
    }
    // VISA
    else if ((length == 13 || length == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
