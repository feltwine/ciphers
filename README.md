# Cipher Program

This is a command-line program that performs encryption and decryption using classic ciphers. It is a school project where new ciphers are added weekly.

## Overview

The program currently supports two ciphers:

- **Caesar Cipher**: A simple substitution cipher where each letter in the plaintext is shifted a certain number of places down or up the alphabet.
- **Rail Fence Cipher**: A transposition cipher that writes the message in a zigzag pattern and reads it off row by row.

## Usage

To run the program, use the following command:
```
./cipher <cipher> <option> <key> <file>
```

### Parameters

- `<cipher>`:
  - `-c` or `--caesar`: Use the Caesar cipher.
  - `-rf` or `--rail-fence`: Use the Rail Fence cipher.

- `<option>`:
  - `-e` or `--encrypt`: Encrypt the input file.
  - `-d` or `--decrypt`: Decrypt the input file.

- `<key>`: An integer defining the shift for the Caesar cipher or the number of rails for the Rail Fence cipher.

- `<file>`: The path to the input file containing the text to be processed.

### Example

To encrypt a file `example.txt` using the Caesar cipher with a shift of 3:
```
./cipher -c -e 3 example.txt
```

To decrypt the same file using the Rail Fence cipher with 3 rails:
```
./cipher -rf -d 3 example.txt.enc
```

## Future Plans

- Additional ciphers will be added weekly, including both encryption and decryption functionalities.
- Contributions and suggestions for new ciphers are welcome!

## Contribution

This project is open for anyone to fork and use. Feel free to explore, modify, and enhance it for your own use.

## Error Handling

The program checks for valid command-line arguments and prints usage instructions if they are incorrect. It handles errors related to file operations and provides relevant error messages.

## Requirements

- A C compiler (e.g., `gcc`) to compile the source code.
- The program has been tested on Linux systems, particularly Fedora 40 with the Budgie desktop environment.

## Implementation Details

The main components of the program include:

- **caesar.h / caesar.c**: Functions for Caesar cipher encryption and decryption.
- **rail-fence.h / rail-fence.c**: Functions for Rail Fence cipher encryption and decryption.
- The main program logic in `main.c`, which handles user input and orchestrates the encryption/decryption process.

## License

This project falls under no specific license. Feel free to fork and modify it for your own use!

## Acknowledgments

Inspired by classic cryptography techniques. Contributions and improvements are welcome!
