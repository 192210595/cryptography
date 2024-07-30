#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define NUM_TOP_PLAINTEXTS 10
const float english_freq[ALPHABET_SIZE] = {
    8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4,
    6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1
};
void calculateFrequency(const char *text, float *frequency) {
    int total_letters = 0;
    int i;
    for (i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            frequency[tolower(text[i]) - 'a']++;
            total_letters++;
        }
    }
    if (total_letters > 0) {
        for (i = 0; i < ALPHABET_SIZE; i++) {
            frequency[i] = (frequency[i] / total_letters) * 100;
        }
    }
}
float scoreFrequency(float *freq1, float *freq2) {
    float score = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += abs(freq1[i] - freq2[i]);
    }
    return score;
}
void decrypt(const char *ciphertext, char *mapping, char *plaintext) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            plaintext[i] = mapping[ciphertext[i] - base] + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
void frequencyAttack(const char *ciphertext, int num_results) {
    float ciphertext_freq[ALPHABET_SIZE] = {0};
    calculateFrequency(ciphertext, ciphertext_freq);

    char mapping[ALPHABET_SIZE];
    float min_score = 1000;
    char plaintext[strlen(ciphertext) + 1];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            mapping[j] = (i + j) % ALPHABET_SIZE;
        }

        decrypt(ciphertext, mapping, plaintext);
        float plaintext_freq[ALPHABET_SIZE] = {0};
        calculateFrequency(plaintext, plaintext_freq);

        float score = scoreFrequency(ciphertext_freq, plaintext_freq);
        if (score < min_score) {
            min_score = score;
            memcpy(mapping, plaintext, ALPHABET_SIZE);
        }
    }
    printf("Top %d possible plaintexts:\n", num_results);
    for (int i = 0; i < num_results; i++) {
        decrypt(ciphertext, mapping, plaintext);
        printf("%d. Plaintext: %s\n", i + 1, plaintext);
        min_score = 1000; 
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            mapping[j] = (mapping[j] + 1) % ALPHABET_SIZE;
        }
    }
}

int main() {
    char ciphertext[] = "Xlmw irgvCtxih qiwweki wlepp gpevmjC lsA rsx erh gsqqirxw mw sj xliC lsA rsx erh gsqqirxw mw.";
    int num_results = NUM_TOP_PLAINTEXTS;

    frequencyAttack(ciphertext, num_results);

    return 0;
}

