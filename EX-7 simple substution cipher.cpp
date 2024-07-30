#include <stdio.h>
#include <string.h>

void decryptSubstitution(char* ciphertext, char* substitutionMap) {
    
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= '0' && ciphertext[i] <= '9') {
          
            printf("%c", substitutionMap[ciphertext[i] - '0' + 26]);
        } else if (ciphertext[i] >= '(' && ciphertext[i] <= '9') {
         
            printf("%c", substitutionMap[ciphertext[i] - '(' + 36]);
        } else if (ciphertext[i] == ' ') {
         
            printf(" ");
        } else {
           
            printf("%c", substitutionMap[ciphertext[i] - 'A']);
        }
    }

    printf("\n");
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";

    char substitutionMap[128] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789()*;:[]—";

    char e_guess = 'e';
    char most_frequent_char = 'B';  
    substitutionMap[most_frequent_char - 'A'] = e_guess;

    char t_guess = 't';
    char h_guess = 'h';
    char second_most_frequent_char = 'U';  
    substitutionMap[second_most_frequent_char - 'A'] = t_guess;

    char common_pair_guess = 'm';
   
    substitutionMap[common_pair_guess - 'A'] = h_guess;

    decryptSubstitution(ciphertext, substitutionMap);

    return 0;
}
