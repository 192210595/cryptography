#include <stdio.h>
#include <string.h>

void hillEncrypt(char *message, int key[2][2]) {
    int len = strlen(message);

    // Adjust the length to be even by appending 'x' if necessary
    if (len % 2 != 0) {
        message[len] = 'x';
        message[len + 1] = '\0';
        len++;
    }

    for (int i = 0; i < len; i += 2) {
        int x1 = message[i] - 'a';
        int x2 = message[i + 1] - 'a';

        int y1 = (key[0][0] * x1 + key[0][1] * x2) % 26;
        int y2 = (key[1][0] * x1 + key[1][1] * x2) % 26;

        printf("%c%c ", 'a' + y1, 'a' + y2);
    }

    printf("\n");
}

int main() {
    char message[] = "meet me at the usual place at ten rather than eight o'clock";
    int key[2][2] = {{9, 4}, {5, 7}};

    printf("Original Message: %s\n", message);
    printf("Encrypted Message: ");
    hillEncrypt(message, key);

    return 0;
}
