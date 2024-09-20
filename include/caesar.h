#ifndef CAESAR_H
#define CAESAR_H

/**
 * Encrypts the given text using the Caesar cipher.
 *
 * @param text  The input text to encrypt. The text is modified in place.
 * @param shift The number of positions to shift each alphabetic character.
 */
void c_encrypt(char text[], int shift);

/**
 * Decrypts the given text using the Caesar cipher.
 *
 * @param text  The input text to decrypt. The text is modified in place.
 * @param shift The number of positions to shift each alphabetic character.
 */
void c_decrypt(char text[], int shift);

#endif // CAESAR_H
