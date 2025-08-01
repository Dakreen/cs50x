#include <cs50.h>  // CS50 library for get_int()
#include <stdio.h> // Standard I/O library for printf()

int main(void)
{
    int height;

    // Prompt the user for a height between 1 and 8 (inclusive)
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height > 8);  // Repeat if input is invalid

    // Loop through each line of the pyramid
    for (int lineNumber = 1; lineNumber <= height; lineNumber++)
    {
        // Calculate and print spaces before the left hashes
        int blankSpace = height - lineNumber;
        for (int i = 0; i < blankSpace; i++)
        {
            printf(" ");
        }

        // Print left side of the pyramid
        int hashtagNumber = lineNumber;
        for (int j = 0; j < hashtagNumber; j++)
        {
            printf("#");
        }

        // Print the gap between the two halves
        printf("  ");

        // Print right side of the pyramid
        for (int k = 0; k < hashtagNumber; k++)
        {
            printf("#");
        }

        // Move to the next line
        printf("\n");
    }
}
