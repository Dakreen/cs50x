#include <cs50.h>
#include <stdio.h>

// Function prototypes
bool checksum(long number);
int numberLength(long number);

int main(void)
{
    // Prompt user for a credit card number
    long number = get_long("Number: ");
    long copyNumber = number;

    // Count number of digits
    int numDigits = numberLength(number);

    // Check if length is potentially valid for major card types
    if (numDigits == 13 || numDigits == 15 || numDigits == 16)
    {
        // Prepare to extract leading digits
        long oneDigit = copyNumber;
        long twoDigits = copyNumber;
        long checksumNumber = copyNumber;

        // Calculate how many digits to remove
        int oneDigitLength = numDigits - 1;
        int twoDigitsLength = numDigits - 2;

        int digitsCounter = 0;

        // Get the first digit (for VISA check)
        do
        {
            oneDigit /= 10;
            digitsCounter++;
        }
        while (digitsCounter < oneDigitLength);

        digitsCounter = 0;

        // Get the first two digits (for AMEX/MASTERCARD check)
        do
        {
            twoDigits /= 10;
            digitsCounter++;
        }
        while (digitsCounter < twoDigitsLength);

        // Check for AMEX (15 digits, starts with 34 or 37)
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
        // Check for MASTERCARD or VISA (16 digits)
        else if (numDigits == 16)
        {
            // MASTERCARD: starts with 51–55
            if (twoDigits >= 51 && twoDigits <= 55)
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
            // VISA: starts with 4
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
        // Check for 13-digit VISA
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
        // Reject if the number length isn't valid
        printf("INVALID\n");
    }
}

// Implements Luhn’s algorithm to verify checksum
bool checksum(long number)
{
    int lastDigit;
    int sumPair = 0;
    int sumUnpair = 0;
    int totalSum = 0;
    int left;
    int counter = 1;

    while (number > 0)
    {
        left = counter % 2;

        // Every second digit from the right (even positions)
        if (left == 0)
        {
            int doubleDigit = (number % 10) * 2;

            // If result is two-digit, split and sum them
            if (numberLength(doubleDigit) > 1)
            {
                int second = doubleDigit % 10;
                int first = doubleDigit / 10;
                int extractSum = first + second;
                sumPair += extractSum;
            }
            else
            {
                sumPair += doubleDigit;
            }
        }
        // Odd positions (just add the digit)
        else
        {
            int digit = number % 10;
            sumUnpair += digit;
        }

        number /= 10;
        counter++;
    }

    totalSum = sumPair + sumUnpair;
    lastDigit = totalSum % 10;

    // If total ends in 0, it's valid
    return lastDigit == 0;
}

// Helper to count number of digits in the card number
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
