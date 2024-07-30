#include <stdio.h>
#include <stdint.h>

typedef uint64_t DES_block;
typedef uint32_t DES_subkey;
void generateSubkeys(DES_block key, DES_subkey subkeys[16]);
DES_block encrypt(DES_block plaintext, DES_subkey subkeys[16]);

int main() {
    DES_block plaintext = 0x0123456789ABCDEF; 
    DES_block key = 0x133457799BBCDFF1;       

    DES_subkey subkeys[16];
    generateSubkeys(key, subkeys);

    DES_block ciphertext = encrypt(plaintext, subkeys);

    printf("Plaintext:  %016llX\n", plaintext);
    printf("Key:        %016llX\n", key);
    printf("Ciphertext: %016llX\n", ciphertext);

    return 0;
}
void generateSubkeys(DES_block key, DES_subkey subkeys[16]) {
      for (int round = 0; round < 16; ++round) {
        subkeys[round] = (key >> (28 - round)) | ((key << round) & 0x0FFFFFFF);
    }
}

DES_block encrypt(DES_block plaintext, DES_subkey subkeys[16]) {

    DES_block result = plaintext;

    for (int round = 0; round < 16; ++round) {
       
        result = result ^ subkeys[round];
    }

    return result;
}
