#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

void print_hex(const unsigned char *data, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main() {
    unsigned char key[24] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
                             0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
                             0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};

    unsigned char iv[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    unsigned char plaintext[8] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    unsigned char ciphertext[8];
    unsigned char decryptedtext[8];

    DES_key_schedule ks1, ks2, ks3;

    DES_set_key_checked(&key[0], &ks1);
    DES_set_key_checked(&key[8], &ks2);
    DES_set_key_checked(&key[16], &ks3);

    DES_ncbc_encrypt(plaintext, ciphertext, 8, &ks1, &iv[0], DES_ENCRYPT);
    DES_ncbc_encrypt(ciphertext, decryptedtext, 8, &ks3, &iv[0], DES_DECRYPT);

    printf("Original Text:  ");
    print_hex(plaintext, sizeof(plaintext));

    printf("3DES CBC Text:  ");
    print_hex(ciphertext, sizeof(ciphertext));

    printf("Decrypted Text: ");
    print_hex(decryptedtext, sizeof(decryptedtext));

    return 0;
}

