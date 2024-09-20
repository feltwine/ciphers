#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "caesar.h"
#include "rail-fence.h"

enum CIPHER {
    NONE = 0,
    CAESAR,
    RAIL_FENCE
};

// Define options for encryption and decryption
enum OPTION {
    OPTION_NONE = 0,
    OPTION_ENCRYPT,
    OPTION_DECRYPT
};

#define MAX_BUFFER_SIZE 1024  // Define a maximum buffer size

int main(int argc, char **argv)
{
    enum CIPHER cipher = NONE;
    enum OPTION option = OPTION_NONE;  // Initialize option
    int shift;
    char buffer[MAX_BUFFER_SIZE];
    FILE *inputFile, *outputFile;
    char outputFileName[256];  // To store the name of the new file

    // Check for correct number of arguments
    if (argc != 5) {
        printf("Correct usage: cipher <cipher> <option> <key> <file>\n");
        printf("cipher:  -c, --caesar       Uses caesars cipher\n");
        printf("         -rf --rail-fence   Uses rail-fence cipher\n");
        printf("options: -e, --encrypt      Encrypts file\n");
        printf("         -d, --decrypt      Decrypts file\n\n");
        printf("         key is an integer that defines the shift in the encryption\n");
        return 0;
    }

    // Determine which cipher to use
    if ((strcmp(argv[1], "-c") == 0) || (strcmp(argv[1], "--caesar") == 0))
        cipher = CAESAR;
    if ((strcmp(argv[1], "-rf") == 0) || (strcmp(argv[1], "--rail-fence") == 0))
        cipher = RAIL_FENCE;
    if (cipher == NONE) {
        printf("Wrong cipher!\n");
        return 0;
    }

    // Determine the encryption or decryption option
    if ((strcmp(argv[2], "-e") == 0) || (strcmp(argv[2], "--encrypt") == 0)) {
        option = OPTION_ENCRYPT;
    } else if ((strcmp(argv[2], "-d") == 0) || (strcmp(argv[2], "--decrypt") == 0)) {
        option = OPTION_DECRYPT;
    }

    // Check if a valid option was chosen
    if (option == OPTION_NONE) {
        printf("Wrong option!\n");
        return 0;
    }

    // Convert the key (shift) to an integer
    shift = atoi(argv[3]);

    // Open the input file
    inputFile = fopen(argv[4], "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Read the content of the file
    size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, inputFile);
    if (ferror(inputFile)) {
        perror("Error reading file");
        fclose(inputFile);
        return 1;
    }
    buffer[bytesRead] = '\0';  // Null-terminate the buffer

    // Close the input file
    fclose(inputFile);

    // Perform the cipher operation
    if (cipher == CAESAR && option == OPTION_ENCRYPT)
        c_encrypt(buffer, shift);
    if (cipher == CAESAR && option == OPTION_DECRYPT)
        c_decrypt(buffer, shift);
    if (cipher == RAIL_FENCE && option == OPTION_ENCRYPT)
        rf_encrypt(buffer, bytesRead, shift);  // Corrected to use bytesRead
    if (cipher == RAIL_FENCE && option == OPTION_DECRYPT)
        rf_decrypt(buffer, bytesRead, shift);  // Corrected to use bytesRead

    // Prepare the output file name
    snprintf(outputFileName, sizeof(outputFileName), "%s.%s", argv[4], (option == OPTION_ENCRYPT) ? "enc" : "dec");

    // Open the output file
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        return 1;
    }

    // Write the modified content to the output file
    if (fwrite(buffer, 1, bytesRead, outputFile) != bytesRead) {
        perror("Error writing to file");
        fclose(outputFile);
        return 1;
    }

    // Close the output file
    fclose(outputFile);
    return 0;
}
