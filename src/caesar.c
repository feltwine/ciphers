#include "caesar.h"
#include <stdio.h>

/**
 * Performs Caesar cipher shift on the given text.
 *
 * @param text    The input text to encrypt or decrypt. The text is modified in place.
 * @param shift   The number of positions to shift each alphabetic character.
 * @param encrypt If non-zero, performs encryption; otherwise, performs decryption.
 */
static void caesar_shift(char text[], int shift, int encrypt)
{
    if (text == NULL) {
        fprintf(stderr, "Error: NULL text provided to Caesar cipher.\n");
        return;
    }

    char ch;
    int i = 0;

    // Normalize the shift to be within 0-25
    shift = shift % 26;
    if (shift < 0) {
        shift += 26;
    }

    // For decryption, invert the shift
    if (!encrypt) {
        shift = 26 - shift;
    }

    // Iterate over each character in the text
    while (text[i] != '\0')
    {
        ch = text[i];

        // Encrypt uppercase letters
        if (ch >= 'A' && ch <= 'Z') {
            ch = ((ch - 'A' + shift) % 26 + 'A');
        }
        // Encrypt lowercase letters
        else if (ch >= 'a' && ch <= 'z'){
            ch = ((ch - 'a' + shift) % 26 + 'a');
        }

        // Replace the character in the text
        text[i] = ch;
        i++;
    }
}

// Caesar Cipher Encryption
void c_encrypt(char text[], int shift)
{
    caesar_shift(text, shift, 1);
}

// Caesar Cipher Decryption
void c_decrypt(char text[], int shift)
{
    caesar_shift(text, shift, 0);
}
