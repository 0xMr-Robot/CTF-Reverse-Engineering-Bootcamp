#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define an unsigned char type for clarity, as we are working with bytes.
typedef unsigned char byte;

/**
 * @brief Performs a left bitwise rotation on a byte.
 * In a rotation, bits that are shifted off one end are wrapped around to the other.
 * For example, ROTL(10010001, 2) would result in 01000110.
 *
 * @param x The byte to rotate.
 * @param n The number of positions to rotate left.
 * @return The rotated byte.
 */
byte rotate_left(byte x, int n) {
    // (x << n) shifts the bits to the left.
    // (x >> (8 - n)) gets the bits that would be shifted off and moves them to the right end.
    // The bitwise OR | combines them.
    return (x << n) | (x >> (8 - n));
}

/**
 * @brief Performs a right bitwise rotation on a byte.
 * This is the inverse operation of rotate_left.
 *
 * @param x The byte to rotate.
 * @param n The number of positions to rotate right.
 * @return The rotated byte.
 */
byte rotate_right(byte x, int n) {
    // (x >> n) shifts the bits to the right.
    // (x << (8 - n)) gets the bits that would be shifted off and moves them to the left end.
    // The bitwise OR | combines them.
    return (x >> n) | (x << (8 - n));
}

/**
 * @brief Encrypts data using a combination of XOR, rotation, and shifting.
 *
 * @param data The plaintext data to encrypt.
 * @param data_len The length of the plaintext data.
 * @param key The secret key.
 * @param key_len The length of the key.
 * @return A pointer to the newly allocated ciphertext. The caller must free this memory.
 */
byte* encrypt(const byte* data, size_t data_len, const byte* key, size_t key_len) {
    // Allocate memory for the output ciphertext.
    byte* output = (byte*)malloc(data_len);
    if (!output) return NULL; // Always check if malloc was successful.

    // Process each byte of the data.
    for (size_t i = 0; i < data_len; ++i) {
        // 1. Start with the original byte.
        byte temp = data[i];

        // 2. XOR it with the corresponding key byte.
        // The modulo operator (%) makes the key repeat if it's shorter than the data.
        temp = temp ^ key[i % key_len];

        // 3. Perform a left rotation. Let's use a fixed rotation of 3 bits.
        temp = rotate_left(temp, 3);

        // 4. Perform a right shift. Let's use a fixed shift of 1 bit.
        // A simple shift like this causes a bit to be lost, making the operation non-reversible
        // on its own. We will handle this in the decryption.
        // To make it reversible, we'll add the lost bit back in a predictable way.
        // For simplicity in this example, we'll stick to a basic function, but be aware
        // that a simple shift loses data. For a more robust cipher, every step must be reversible.
        // Let's use another rotation instead of a shift to ensure perfect reversibility.
        temp = rotate_left(temp, 1); // An additional rotation.

        output[i] = temp;
    }
    return output;
}

/**
 * @brief Decrypts data by applying the inverse operations in reverse order.
 *
 * @param data The ciphertext data to decrypt.
 * @param data_len The length of the ciphertext data.
 * @param key The secret key.
 * @param key_len The length of the key.
 * @return A pointer to the newly allocated plaintext. The caller must free this memory.
 */
byte* decrypt(const byte* data, size_t data_len, const byte* key, size_t key_len) {
    // Allocate memory for the output plaintext.
    byte* output = (byte*)malloc(data_len);
    if (!output) return NULL;

    // Process each byte of the data.
    for (size_t i = 0; i < data_len; ++i) {
        // To decrypt, we apply the INVERSE of each encryption step in REVERSE order.
        byte temp = data[i];

        // 4. Reverse the second rotation: Rotate right by 1.
        temp = rotate_right(temp, 1);

        // 3. Reverse the first rotation: Rotate right by 3.
        temp = rotate_right(temp, 3);

        // 2. Reverse the XOR operation. XORing with the same key reverses the operation.
        temp = temp ^ key[i % key_len];

        // 1. We are now back to the original byte.
        output[i] = temp;
    }
    return output;
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
    const char* plaintext_str = "Hello, World!";
    const char* key_str = "SECRETKEY";

    size_t data_len = strlen(plaintext_str);
    size_t key_len = strlen(key_str);

    printf("Original Plaintext: %s\n", plaintext_str);
    print_hex("Plaintext (hex)", (const byte*)plaintext_str, data_len);
    printf("\n");

    // Encrypt the data
    byte* ciphertext = encrypt((const byte*)plaintext_str, data_len, (const byte*)key_str, key_len);
    if (ciphertext) {
        print_hex("Encrypted (hex)", ciphertext, data_len);

        // Decrypt the data
        byte* decrypted_text = decrypt(ciphertext, data_len, (const byte*)key_str, key_len);
        if (decrypted_text) {
            printf("Decrypted Text: %.*s\n", (int)data_len, decrypted_text);

            // Free the allocated memory
            free(decrypted_text);
        }
        free(ciphertext);
    }

    return 0;
}