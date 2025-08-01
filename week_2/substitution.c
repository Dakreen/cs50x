#include <cs50.h>      // For get_string()
#include <ctype.h>     // For isalpha(), toupper(), tolower()
#include <stdio.h>     // For printf()
#include <string.h>    // For strlen(), string functions

// Key test examples (valid): 
// NQXPOMAFTRHLZGECYJIUWSKDVB
// NqXpOmAfTrHlZgEcYjIuWsKdVb
// nqxpomaftrhlzgecyjiuwskdvb

// Constants
const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int LENGTH = strlen(ALPHABET);

// Function declarations
bool key_checker(string key);       // Validates the key
string cipher(string text, string key); // Encrypts the plaintext using the key

int main(int argc, string argv[])
{
    // Ensure user provides exactly one command-line argument
    if (argc == 2)
    {
        string key = argv[1];

        // Validate the key
        if (key_checker(key))
        {
            // Prompt for plaintext
            string text = get_string("plaintext: ");

            // Encrypt the text using the substitution cipher
            string cipher_text = cipher(text, key);

            // Output the ciphertext
            printf("ciphertext: %s\n", cipher_text);
        }
        else
        {
            // Key is invalid, exit with error
            return 1;
        }
        return 0;
    }
    else
    {
        // If incorrect number of arguments is passed
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

// Function that checks if the key is valid (26 unique alphabetic characters)
bool key_checker(string key)
{
    int key_length = strlen(key);

    // Check length of the key
    if (key_length == LENGTH)
    {
        for (int i = 0; i < key_length; i++)
        {
            if (isalpha(key[i])) // Ensure character is alphabetic
            {
                // Check for duplicate characters (case-insensitive)
                for (int j = 0; j < i; j++)
                {
                    if (toupper(key[i]) == toupper(key[j]))
                    {
                        printf("Key must contain each letter exactly once.\n");
                        return false;
                    }
                }
            }
            else
            {
                // If a non-letter character is found
                printf("Key must contain only alphabetic characters.\n");
                return false;
            }
        }
        return true; // Key is valid
    }
    else
    {
        // If key length is not 26
        printf("Key must contain 26 characters.\n");
        return false;
    }
}

// Function that applies the substitution cipher
string cipher(string text, string key)
{
    int text_length = strlen(text);
    string cipher_text = text; // Reuse same memory (safe in CS50.dev)

    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(text[i])) // Only encrypt alphabetic characters
        {
            // Loop through alphabet to find matching character
            for (int j = 0; j < LENGTH; j++)
            {
                if (toupper(ALPHABET[j]) == toupper(text[i]))
                {
                    // Maintain original case
                    if (islower(text[i]) && isupper(key[j]))
                    {
                        cipher_text[i] = tolower(key[j]);
                        break;
                    }
                    else if (isupper(text[i]) && islower(key[j]))
                    {
                        cipher_text[i] = toupper(key[j]);
                        break;
                    }
                    else
                    {
                        cipher_text[i] = key[j];
                        break;
                    }
                }
            }
        }
        else
        {
            // Leave non-alphabetic characters unchanged
            cipher_text[i] = text[i];
        }
    }
    return cipher_text;
}
