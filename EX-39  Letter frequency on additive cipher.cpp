#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate the frequency of each letter in a string
void calculateFrequency(const char *text, int *frequency) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            frequency[tolower(text[i]) - 'a']++;
        }
    }
}

// Function to decrypt the ciphertext using a given shift
void decrypt(const char *ciphertext, int shift, char *plaintext) {
    int i;
    for (i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            plaintext[i] = ((ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

// Function to perform a letter frequency attack on an additive cipher
void frequencyAttack(const char *ciphertext, int num_results) {
    int frequency[ALPHABET_SIZE] = {0};
    calculateFrequency(ciphertext, frequency);

    // Calculate the most frequent letter in the ciphertext
    int max_frequency = 0;
    int max_index = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > max_frequency) {
            max_frequency = frequency[i];
            max_index = i;
        }
    }

    // Assuming the most frequent letter corresponds to 'e', find the shift
    int shift = (max_index + ALPHABET_SIZE - ('e' - 'a')) % ALPHABET_SIZE;

    // Decrypt the ciphertext using the calculated shift
    char plaintext[strlen(ciphertext) + 1];
    decrypt(ciphertext, shift, plaintext);

    // Print the decrypted plaintext
    printf("Top %d possible plaintexts:\n", num_results);
    for (int i = 0; i < num_results; i++) {
        printf("%d. Shift: %d, Plaintext: %s\n", i + 1, shift, plaintext);
        shift = (shift + 1) % ALPHABET_SIZE; // Increment the shift for the next possible plaintext
        decrypt(ciphertext, shift, plaintext); // Update the plaintext with the new shift
    }
}

int main() {
    char ciphertext[] = "Uifsf jt b tfdsfu mbxt, xjui uif npwjf pg uif fyufoe xip xboufe up ijt dpwfsjoh.";
    int num_results = 10; // Number of possible plaintexts to display

    frequencyAttack(ciphertext, num_results);

    return 0;
}

