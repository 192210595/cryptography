#include <stdio.h>
#include <stdlib.h>
#include <openssl/dsa.h>
#include <openssl/sha.h>
#include <openssl/err.h>
void print_hex(const char* label, const unsigned char* data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", data[i]);
    }
    printf("\n");
}
void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}
void dsa_signature_example() {
    DSA *dsa = NULL;
    DSA_SIG *signature = NULL;
    unsigned char hash[SHA_DIGEST_LENGTH];
    dsa = DSA_generate_parameters(1024, NULL, 0, NULL, NULL, NULL, NULL);
    if (dsa == NULL) {
        handleErrors();
    }
    if (!DSA_generate_key(dsa)) {
        handleErrors();
    }
    SHA1((const unsigned char*)MESSAGE, sizeof(MESSAGE) - 1, hash);
    signature = DSA_do_sign(hash, SHA_DIGEST_LENGTH, dsa);
    if (signature == NULL) {
        handleErrors();
    }
    printf("DSA Signature:\n");
    print_hex("r", (unsigned char*)&(signature->r), BN_num_bytes(signature->r));
    print_hex("s", (unsigned char*)&(signature->s), BN_num_bytes(signature->s));
    int verify_result = DSA_do_verify(hash, SHA_DIGEST_LENGTH, signature, dsa);
    if (verify_result == 1) {
        printf("DSA Signature verified successfully.\n");
    } else if (verify_result == 0) {
        printf("DSA Signature verification failed.\n");
    } else {
        handleErrors();
    }
    DSA_free(dsa);
    DSA_SIG_free(signature);
}
int main() {
    printf("Message: %s\n\n", MESSAGE);
    dsa_signature_example();
    return 0;
}

