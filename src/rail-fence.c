#include "rail-fence.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to encrypt data using Rail Fence Cipher
void rf_encrypt(char data[], int dataLength, int key)
{
    if (key <= 1 || key > dataLength) {
        fprintf(stderr, "Invalid key value for encryption. Key must be > 1 and <= data length.\n");
        return;
    }

    // Allocate memory for rail
    char **rail = malloc(key * sizeof(char *));
    if (!rail) {
        perror("Memory allocation failed for rail");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < key; i++) {
        rail[i] = malloc(dataLength * sizeof(char));
        if (!rail[i]) {
            perror("Memory allocation failed for rail row");
            for (int j = 0; j < i; j++) {
                free(rail[j]);
            }
            free(rail);
            exit(EXIT_FAILURE);
        }
        memset(rail[i], '\n', dataLength);
    }

    int dirDown = 0;
    int row = 0, col = 0;

    // Mark the places with actual characters
    for (int i = 0; i < dataLength; i++) {
        if (row == 0) dirDown = 1;
        if (row == key - 1) dirDown = 0;

        rail[row][col++] = data[i];

        if (dirDown)
            row++;
        else
            row--;
    }

    // Read the characters row by row
    int index = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < dataLength; j++) {
            if (rail[i][j] != '\n') {
                data[index++] = rail[i][j];
            }
        }
    }
    data[index] = '\0';

    // Free allocated memory
    for (int i = 0; i < key; i++) {
        free(rail[i]);
    }
    free(rail);
}

// Function to decrypt data using Rail Fence Cipher
void rf_decrypt(char data[], int dataLength, int key)
{
    if (key <= 1 || key > dataLength) {
        fprintf(stderr, "Invalid key value for decryption. Key must be > 1 and <= data length.\n");
        return;
    }

    // Allocate memory for rail
    char **rail = malloc(key * sizeof(char *));
    if (!rail) {
        perror("Memory allocation failed for rail");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < key; i++) {
        rail[i] = malloc(dataLength * sizeof(char));
        if (!rail[i]) {
            perror("Memory allocation failed for rail row");
            for (int j = 0; j < i; j++) {
                free(rail[j]);
            }
            free(rail);
            exit(EXIT_FAILURE);
        }
        memset(rail[i], '\n', dataLength);
    }

    // Mark the places with '*'
    int dirDown = 0;
    int row = 0, col = 0;
    for (int i = 0; i < dataLength; i++) {
        if (row == 0) dirDown = 1;
        if (row == key - 1) dirDown = 0;

        rail[row][col++] = '*';

        if (dirDown)
            row++;
        else
            row--;
    }

    // Now, fill the '*' positions with actual characters from data
    int index = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < dataLength; j++) {
            if (rail[i][j] == '*' && index < dataLength) {
                rail[i][j] = data[index++];
            }
        }
    }

    // Now, read the matrix in zig-zag manner to construct the decrypted text
    row = 0;
    col = 0;
    dirDown = 0;
    for (int i = 0; i < dataLength; i++) {
        if (row == 0) dirDown = 1;
        if (row == key - 1) dirDown = 0;

        if (rail[row][col] != '*') {
            data[i] = rail[row][col++];
        } else {
            // This case should not happen if encryption and decryption are correct
            data[i] = '\0';
            break;
        }

        if (dirDown)
            row++;
        else
            row--;
    }

    // Null-terminate the string
    if (dataLength < 1024 - 1) {  // Assuming MAX_BUFFER_SIZE is 1024
        data[dataLength] = '\0';
    }

    // Free allocated memory
    for (int i = 0; i < key; i++) {
        free(rail[i]);
    }
    free(rail);
}
