#include <cs50.h>
#include <stdio.h>

// Function prototypes
bool checksum(long number);       // Applies Luhn's Algorithm to validate card number
int numberLength(long number);    // Returns number of digits in the card number

int main(void)
{
    // Prompt user for credit card number
    long number = get_long("Number: ");
    long copyNumber = number;

    // Get number of digits in the card number
    int numDigits = numberLength(number);

    // Valid card numbers are 13, 15, or 16 digits long
    if (numDigits == 13 || numDigits == 15 || numDigits == 16)
    {
        // Variables to extract starting digits
        long oneDigit = copyNumber;   // First digit
        long twoDigits = copyNumber;  // First two digits
        long checksumNumber = copyNumber; // For Luhn's algorithm

        int oneDigitLength = numDigits - 1;   // Position of first digit
        int twoDigitsLength = numDigits - 2;  // Position of first two digits
        int digitsCounter = 0;

        // Extract the first digit
        do
        {
            oneDigit /= 10;
            digitsCounter++;
        }
        while (digitsCounter < oneDigitLength);

        // Reset counter and extract the first two digits
        digitsCounter = 0;
        do
        {
            twoDigits /= 10;
            digitsCounter++;
        }
        while (digitsCounter < twoDigitsLength);

        // === Card Type Checks ===

        // American Express: 15 digits, starts with 34 or 37
        if (numDigits == 15)
        {
            if (twoDigits == 34 || twoDigits == 37)
            {
                if (checksum(copyNumber))
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        // 16-digit cards can be MasterCard or Visa
        else if (numDigits == 16)
        {
            // MasterCard: starts with 51–55
            if (twoDigits == 51 || twoDigits == 52 || twoDigits == 53 || twoDigits == 54 ||
                twoDigits == 55)
            {
                if (checksum(copyNumber))
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            // Visa: starts with 4
            else if (oneDigit == 4)
            {
                if (checksum(copyNumber))
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        // 13-digit Visa check
        else if (numDigits == 13)
        {
            if (oneDigit == 4)
            {
                if (checksum(copyNumber))
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
    else
    {
        // Any other length is invalid
        printf("INVALID\n");
    }
}

// === Luhn's Algorithm Implementation ===
// Checks if a card number is valid by summing digits according to Luhn's rules:
// 1. Starting from the second-to-last digit, double every other digit.
// 2. If doubling gives a two-digit number, add the digits together.
// 3. Sum all these doubled results with the sum of digits not doubled.
// 4. If total sum % 10 == 0 → valid card.
bool checksum(long number)
{
    int lastDigit;
    int sumPair = 0;     // Sum of doubled digits
    int sumUnpair = 0;   // Sum of untouched digits
    int totalSum = 0;
    int left;
    int counter = 1;     // Position counter from right to left

    while (number > 0)
    {
        left = counter % 2;

        if (left == 0)
        {
            // Double every second digit from the right
            int doubleDigit = (number % 10) * 2;

            // If doubling creates a two-digit number, add both digits separately
            if (numberLength(doubleDigit) > 1)
            {
                int first = doubleDigit / 10;
                int second = doubleDigit % 10;
                sumPair += first + second;
            }
            else
            {
                sumPair += doubleDigit;
            }
        }
        else
        {
            // Add digits not doubled
            int digit = number % 10;
            sumUnpair += digit;
        }

        number /= 10;
        counter++;
    }

    totalSum = sumPair + sumUnpair;
    lastDigit = totalSum % 10;

    return (lastDigit == 0);
}

// Returns the number of digits in a number
int numberLength(long number)
{
    int length = 0;
    while (number > 0)
    {
        number /= 10;
        length++;
    }
    return length;
}
