#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

// RC5 Encryption Algorithm Implementation
// RC5 is a symmetric key block cipher known for its simplicity and efficiency

// RC5 parameters - these define the variant (RC5-w/r/b)
#define WORD_SIZE 32        // w: word size in bits (32 for RC5-32)
#define ROUNDS 12           // r: number of rounds
#define KEY_BYTES 16        // b: key length in bytes (16 for 128-bit key)

// Derived constants
#define WORD_BYTES (WORD_SIZE / 8)
#define KEY_WORDS (KEY_BYTES / WORD_BYTES)
#define EXPANDED_KEY_SIZE (2 * (ROUNDS + 1))

// Magic constants for key expansion (derived from e and phi)
#define P32 0xB7E15163      // Magic constant for 32-bit words
#define Q32 0x9E3779B9      // Magic constant for 32-bit words

// Circular left shift function
uint32_t left_rotate(uint32_t value, uint32_t shift) {
    // Rotate bits to the left by 'shift' positions
    // This provides diffusion in the encryption process
    return (value << shift) | (value >> (WORD_SIZE - shift));
}

// Circular right shift function
uint32_t right_rotate(uint32_t value, uint32_t shift) {
    // Rotate bits to the right by 'shift' positions
    // This is the inverse operation of left rotation
    return (value >> shift) | (value << (WORD_SIZE - shift));
}

// Key expansion function
void rc5_expand_key(const uint8_t* key, uint32_t* S) {
    /*
    Key Expansion Process:
    1. Convert secret key from bytes to words
    2. Initialize expanded key array with magic constants
    3. Mix the secret key into the expanded key array
    */

    uint32_t L[KEY_WORDS];
    uint32_t i, j, A, B;

    // Step 1: Convert key bytes to words (little-endian)
    for (i = 0; i < KEY_WORDS; i++) {
        L[i] = 0;
        for (j = 0; j < WORD_BYTES; j++) {
            L[i] = (L[i] << 8) + key[i * WORD_BYTES + j];
        }
    }

    // Step 2: Initialize expanded key array S
    S[0] = P32;
    for (i = 1; i < EXPANDED_KEY_SIZE; i++) {
        S[i] = S[i - 1] + Q32;
    }

    // Step 3: Mix the key into the expanded key array
    A = B = 0;
    i = j = 0;
    uint32_t n = 3 * (EXPANDED_KEY_SIZE > KEY_WORDS ? EXPANDED_KEY_SIZE : KEY_WORDS);

    for (uint32_t k = 0; k < n; k++) {
        A = S[i] = left_rotate(S[i] + A + B, 3);
        B = L[j] = left_rotate(L[j] + A + B, (A + B) % WORD_SIZE);

        i = (i + 1) % EXPANDED_KEY_SIZE;
        j = (j + 1) % KEY_WORDS;
    }
}

// RC5 Encryption function
void rc5_encrypt(const uint32_t* S, const uint32_t* plaintext, uint32_t* ciphertext) {
    /*
    Encryption Process:
    1. Split 64-bit block into two 32-bit words (A and B)
    2. Add expanded key words to A and B
    3. Perform R rounds of mixing using rotations and XOR
    4. Output the final A and B as ciphertext
    */

    uint32_t A = plaintext[0] + S[0];
    uint32_t B = plaintext[1] + S[1];

    // Main encryption rounds
    for (int i = 1; i <= ROUNDS; i++) {
        // Feistel network operations
        A = left_rotate(A ^ B, B % WORD_SIZE) + S[2 * i];
        B = left_rotate(B ^ A, A % WORD_SIZE) + S[2 * i + 1];
    }

    ciphertext[0] = A;
    ciphertext[1] = B;
}

// RC5 Decryption function
void rc5_decrypt(const uint32_t* S, const uint32_t* ciphertext, uint32_t* plaintext) {
    /*
    Decryption Process:
    1. Reverse the encryption process
    2. Start with ciphertext words A and B
    3. Perform inverse operations in reverse order
    4. Subtract expanded key words at the end
    */

    uint32_t A = ciphertext[0];
    uint32_t B = ciphertext[1];

    // Main decryption rounds (in reverse order)
    for (int i = ROUNDS; i >= 1; i--) {
        // Inverse Feistel network operations
        B = right_rotate(B - S[2 * i + 1], A % WORD_SIZE) ^ A;
        A = right_rotate(A - S[2 * i], B % WORD_SIZE) ^ B;
    }

    plaintext[0] = A - S[0];
    plaintext[1] = B - S[1];
}

// Helper function to display data in hexadecimal
void print_hex(const char* label, const uint8_t* data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02X", data[i]);
    }
    printf("\n");
}

int main() {
    printf("=== RC5 Encryption Algorithm Demo ===\n\n");

    // Test key (16 bytes = 128 bits)
    uint8_t key[KEY_BYTES] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
        0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10
    };

    // Test plaintext (8 bytes = 64 bits)
    uint8_t plaintext[8] = { 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0 };
    uint32_t plaintext_words[2];
    uint32_t ciphertext_words[2];
    uint32_t decrypted_words[2];
    uint8_t ciphertext[8];
    uint8_t decrypted[8];

    // Expand the key
    uint32_t S[EXPANDED_KEY_SIZE];
    rc5_expand_key(key, S);

    printf("RC5 Parameters: w=%d, r=%d, b=%d\n", WORD_SIZE, ROUNDS, KEY_BYTES);
    print_hex("Key", key, KEY_BYTES);
    print_hex("Plaintext", plaintext, 8);

    // Convert plaintext to words
    memcpy(plaintext_words, plaintext, 8);

    // Encrypt
    rc5_encrypt(S, plaintext_words, ciphertext_words);
    memcpy(ciphertext, ciphertext_words, 8);
    print_hex("Ciphertext", ciphertext, 8);

    // Decrypt
    rc5_decrypt(S, ciphertext_words, decrypted_words);
    memcpy(decrypted, decrypted_words, 8);
    print_hex("Decrypted", decrypted, 8);

    // Verify
    if (memcmp(plaintext, decrypted, 8) == 0) {
        printf("\n✓ Encryption/Decryption successful!\n");
    }
    else {
        printf("\n✗ Encryption/Decryption failed!\n");
    }

    return 0;
}