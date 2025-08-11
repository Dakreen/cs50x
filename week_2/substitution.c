#include <cs50.h>     // For get_string() and CS50 string type
#include <ctype.h>    // For isalpha(), isupper(), islower(), toupper(), tolower()
#include <stdio.h>    // For printf()
#include <string.h>   // For strlen()

// Example valid keys (26 unique alphabetic characters, any case):
// "NQXPOMAFTRHLZGECYJIUWSKDVB"
// "NqXpOmAfTrHlZgEcYjIuWsKdVb"
// "nqxpomaftrhlzgecyjiuwskdvb"

// Constant alphabet reference (uppercase)
const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int LENGTH = strlen(ALPHABET); // Length of the alphabet (26)

// Function prototypes
bool key_checker(string key);      // Validates the provided key
string cipher(string text, string key); // Encrypts text using the substitution key

int main(int argc, string argv[])
{
    // Ensure the user provided exactly one command-line argument (the key)
    if (argc == 2)
    {
        string key = argv[1];

        // Validate the key
        if (key_checker(key))
        {
            // Prompt user for plaintext to encrypt
            string text = get_string("plaintext: ");

            // Encrypt the plaintext using the key
            string cipher_text = cipher(text, key);

            // Output the encrypted result
            printf("ciphertext: %s\n", cipher_text);
        }
        else
        {
            // Invalid key → exit with error code
            return 1;
        }
        return 0;
    }
    else
    {
        // User did not provide the key correctly
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

/*
 * key_checker:
 * Validates the key according to three rules:
 * 1. Must contain exactly 26 characters.
 * 2. Every character must be alphabetic (A–Z or a–z).
 * 3. No duplicate characters (case-insensitive).
 * Returns true if valid, false otherwise.
 */
bool key_checker(string key)
{
    int key_length = strlen(key);

    // Rule 1: Key must have 26 characters
    if (key_length == LENGTH)
    {
        for (int i = 0; i < key_length; i++)
        {
            // Rule 2: Each character must be alphabetic
            if (isalpha(key[i]))
            {
                // Rule 3: Check for duplicates by comparing with all previous characters
                if (i > 0)
                {
                    for (int j = 0; j < i; j++)
                    {
                        // Compare letters case-insensitively
                        if (toupper(key[i]) == toupper(key[j]))
                        {
                            printf("Key must contain each letter exactly once.\n");
                            return false;
                        }
                    }
                }
            }
            else
            {
                // Non-alphabetic character found
                printf("Key must contain 26 alphabetic characters.\n");
                return false;
            }
        }
        // All checks passed → key is valid
        return true;
    }
    else
    {
        // Wrong length
        printf("Key must contain 26 characters.\n");
        return false;
    }
}

/*
 * cipher:
 * Encrypts the given plaintext using the provided substitution key.
 * - Maintains letter case (uppercase stays uppercase, lowercase stays lowercase).
 * - Non-alphabetic characters remain unchanged.
 * Returns the ciphertext as a string.
 */
string cipher(string text, string key)
{
    int text_length = strlen(text);
    string cipher_text = text; // Start with plaintext as base

    // Loop through each character of the plaintext
    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(text[i])) // Only encrypt letters
        {
            // Find the position of this letter in the alphabet (0–25)
            for (int j = 0; j < LENGTH; j++)
            {
                if (toupper(ALPHABET[j]) == toupper(text[i]))
                {
                    // Preserve case:
                    // If plaintext letter is lowercase but key letter is uppercase
                    if (islower(text[i]) && isupper(key[j]))
                    {
                        cipher_text[i] = tolower(key[j]);
                        break;
                    }
                    // If plaintext letter is uppercase but key letter is lowercase
                    else if (isupper(text[i]) && islower(key[j]))
                    {
                        cipher_text[i] = toupper(key[j]);
                        break;
                    }
                    // Same case → use key letter directly
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
            // Non-alphabetic → copy as-is
            cipher_text[i] = text[i];
        }
    }
    return cipher_text;
}
