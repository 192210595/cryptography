#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to count the frequency of each letter in the text
void count_letter_frequency(const char *text, int *frequency) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            frequency[tolower(text[i]) - 'a']++;
        }
    }
}

// Function to decrypt the ciphertext using a given key
void decrypt(const char *ciphertext, const char *key, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = key[ciphertext[i] - base - 'A'];
        } else {
            plaintext[i] = ciphertext[i]; // Preserve non-alphabetic characters
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Function to sort the plaintexts based on letter frequency
void sort_plaintexts(char **plaintexts, int *frequency, int num_plaintexts) {
    for (int i = 0; i < num_plaintexts - 1; i++) {
        for (int j = i + 1; j < num_plaintexts; j++) {
            int freq_i = 0, freq_j = 0;
            for (int k = 0; plaintexts[i][k] != '\0'; k++) {
                if (isalpha(plaintexts[i][k])) {
                    freq_i += frequency[tolower(plaintexts[i][k]) - 'a'];
                }
            }
            for (int k = 0; plaintexts[j][k] != '\0'; k++) {
                if (isalpha(plaintexts[j][k])) {
                    freq_j += frequency[tolower(plaintexts[j][k]) - 'a'];
                }
            }
            if (freq_i < freq_j) {
                char *temp = plaintexts[i];
                plaintexts[i] = plaintexts[j];
                plaintexts[j] = temp;
            }
        }
    }
}

int main() {
    char ciphertext[1000];
    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    if (strlen(ciphertext) > 0 && ciphertext[strlen(ciphertext) - 1] == '\n') {
        ciphertext[strlen(ciphertext) - 1] = '\0';
    }

    int frequency[ALPHABET_SIZE] = {0};
    count_letter_frequency(ciphertext, frequency);

    char key[ALPHABET_SIZE + 1] = "ETAOINSHRDLCUMWFGYPBVKJXQZ"; // English letter frequency order

    printf("Top N possible plaintexts (N <= %d): ", ALPHABET_SIZE);
    int N;
    scanf("%d", &N);

    char **plaintexts = (char **)malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++) {
        plaintexts[i] = (char *)malloc((strlen(ciphertext) + 1) * sizeof(char));
        decrypt(ciphertext, key, plaintexts[i]);
    }

    sort_plaintexts(plaintexts, frequency, N);

    printf("Possible plaintexts in rough order of likelihood:\n");
    for (int i = 0; i < N; i++) {
        printf("%s\n", plaintexts[i]);
        free(plaintexts[i]);
    }
    free(plaintexts);

    return 0;
}
	
