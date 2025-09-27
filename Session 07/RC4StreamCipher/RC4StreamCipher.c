#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a type for a single byte.
typedef unsigned char byte;

/**
 * @brief This structure holds the state of the RC4 cipher.
 * The state consists of a 256-byte permutation array (the S-box)
 * and two index pointers, 'i' and 'j'.
 */
typedef struct {
    byte S[256];
    byte i;
    byte j;
} rc4_state;

/**
 * @brief A simple helper function to swap two byte values.
 * This is used during the initialization of the S-box.
 *
 * @param a Pointer to the first byte.
 * @param b Pointer to the second byte.
 */
static void swap_bytes(byte* a, byte* b) {
    byte temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Initializes the RC4 state using the given key.
 * This is the Key-Scheduling Algorithm (KSA).
 * It creates a unique permutation of numbers 0-255 based on the secret key.
 *
 * @param state Pointer to the rc4_state structure to initialize.
 * @param key The secret key.
 * @param key_len The length of the key.
 */
void rc4_init(rc4_state* state, const byte* key, size_t key_len) {
    // Step 1: Fill the S-box with identity values (0, 1, 2, ..., 255).
    for (int i = 0; i < 256; i++) {
        state->S[i] = i;
    }

    // Step 2: Scramble the S-box using the key.
    byte j = 0;
    for (int i = 0; i < 256; i++) {
        // The new 'j' is calculated based on the old 'j', the current S-box value,
        // and the current key byte.
        j = j + state->S[i] + key[i % key_len];

        // Swap the values at positions 'i' and 'j' in the S-box.
        swap_bytes(&state->S[i], &state->S[j]);
    }

    // Initialize the index pointers to zero for the start of encryption/decryption.
    state->i = 0;
    state->j = 0;
}

/**
 * @brief Processes data using the RC4 algorithm.
 * This is the Pseudo-Random Generation Algorithm (PRGA).
 * It generates a stream of pseudo-random bytes (the "keystream") and XORs it
 * with the input data. This function works for both encryption and decryption.
 *
 * @param state Pointer to the initialized rc4_state structure.
 * @param data The data to be encrypted or decrypted (this buffer is modified in place).
 * @param data_len The length of the data.
 */
void rc4_crypt(rc4_state* state, byte* data, size_t data_len) {
    for (size_t n = 0; n < data_len; n++) {
        // --- Keystream Generation ---
        // 1. Increment the 'i' pointer.
        state->i++;
        // 2. Update the 'j' pointer using the value from the S-box.
        state->j += state->S[state->i];
        // 3. Swap the values at 'i' and 'j' to further shuffle the S-box.
        swap_bytes(&state->S[state->i], &state->S[state->j]);
        // 4. Find the sum of the two S-box values just swapped.
        byte t = state->S[state->i] + state->S[state->j];
        // 5. Use this sum 't' as an index to find the keystream byte.
        byte keystream_byte = state->S[t];
        // --- End Keystream Generation ---

        // 6. XOR the generated keystream byte with the current data byte.
        data[n] ^= keystream_byte;
    }
}

/**
 * @brief Helper function to print data in hexadecimal format.
 */
void print_hex(const char* label, const byte* data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    const char* key_str = "SecretKey123";
    char plaintext[] = "This is a test message for RC4."; // Use char[] so we can modify it.

    size_t data_len = strlen(plaintext);
    size_t key_len = strlen(key_str);

    printf("Original Plaintext: %s\n", plaintext);
    print_hex("Plaintext (hex)", (const byte*)plaintext, data_len);
    printf("\n");

    // --- Encryption ---
    rc4_state enc_state;
    rc4_init(&enc_state, (const byte*)key_str, key_len);
    rc4_crypt(&enc_state, (byte*)plaintext, data_len);

    print_hex("Encrypted (hex)", (const byte*)plaintext, data_len);
    // Note: The encrypted data is not printable as a string.

    // --- Decryption ---
    // To decrypt, we use a new, re-initialized state and run the same crypt function.
    rc4_state dec_state;
    rc4_init(&dec_state, (const byte*)key_str, key_len);
    rc4_crypt(&dec_state, (byte*)plaintext, data_len);

    printf("Decrypted Text: %s\n", plaintext);
    print_hex("Decrypted (hex)", (const byte*)plaintext, data_len);

    return 0;
}
