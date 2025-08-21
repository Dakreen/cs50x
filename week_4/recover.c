#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// ==========================================================
// CS50x – Problem Set 4: Recover
//
// Program to recover JPEG images from a forensic memory card.
// Strategy:
//   - Read the memory card in 512-byte blocks.
//   - Detect the start of a new JPEG by checking the first 4 bytes.
//   - When a new JPEG header is found:
//       * Close the previous image (if one is open).
//       * Create a new JPEG file with a sequential filename (000.jpg, 001.jpg...).
//   - Continue writing all following blocks into the current file until
//     the next JPEG header is found.
//   - Repeat until the end of the memory card.
//
// Result:
//   Extracted JPEG files are saved in the current directory.
// ==========================================================

int main(int argc, char *argv[])
{
    // Must provide exactly one command-line argument (the memory card filename)
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card for reading
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Cannot open the file\n");
        return 2;
    }

    // Buffer to store each 512-byte block read from the card
    uint8_t buffer[512];

    // File counter for JPEG naming (000.jpg, 001.jpg, …)
    int counter = 0;

    // Pointer to the current JPEG file being written (NULL if none open yet)
    FILE *image = NULL;

    // Read the card block by block (each fread returns number of bytes read)
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Check if this block signals the start of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0) // Mask 0xf0 → check high 4 bits
        {
            // If an image is already open, close it before starting a new one
            if (image != NULL)
            {
                fclose(image);
            }

            // Create a new filename for the next JPEG
            char block_img[8];
            sprintf(block_img, "%03i.jpg", counter);

            // Open the new JPEG file for writing
            image = fopen(block_img, "w");
            counter++;
        }

        // If we are already writing a JPEG, write this 512-byte block to it
        if (counter > 0)
        {
            fwrite(buffer, 1, 512, image);
        }
    }

    // Close the last JPEG file (if one is open)
    if (image != NULL)
    {
        fclose(image);
    }

    // Close the memory card file
    fclose(card);
}