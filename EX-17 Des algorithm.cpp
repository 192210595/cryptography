#include <stdio.h>
#include <stdint.h>

typedef uint64_t DES_block;

DES_block decrypt(DES_block cipherText, DES_block keys[]);
void generateKeys(DES_block key, DES_block keys[]);
int main() {
    
    DES_block plainText = 0x0123456789ABCDEF; 
    DES_block key = 0x133457799BBCDFF1;       

    DES_block keys[16];
    generateKeys(key, keys);

    DES_block decryptedText = decrypt(plainText, keys);

    printf("Decrypted Text: %016llX\n", decryptedText);
    return 0;
}
DES_block decrypt(DES_block cipherText, DES_block keys[]) {
    for (int round = 15; round >= 0; --round) {
        
    }
    return cipherText;
}
void generateKeys(DES_block key, DES_block keys[]) {
   
}
