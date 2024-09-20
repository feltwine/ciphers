#ifndef RAIL_FENCE_H
#define RAIL_FENCE_H

/**
 * @brief Encrypts the input data using the Rail Fence Cipher.
 *
 * Implementation of the Rail Fence Cipher encryption.
 */
void rf_encrypt(char data[], int dataLength, int key);

/**
 * @brief Decrypts the input data encrypted with the Rail Fence Cipher.
 *
 * Implementation of the Rail Fence Cipher decryption.
 */
void rf_decrypt(char data[], int dataLength, int key);

#endif
