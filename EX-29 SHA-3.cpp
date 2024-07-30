#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LANE_BITS 64
#define STATE_SIZE 25 
#define RATE_LANES 16 
#define CAPACITY_LANES (STATE_SIZE - RATE_LANES)
void absorb_message_block(uint64_t state[STATE_SIZE], const uint64_t input[RATE_LANES]) {
	int i;
    for (i = 0; i < RATE_LANES; i++) {
        state[i] ^= input[i];
    }
}

int main() {
    uint64_t state[STATE_SIZE] = {0}; 
    uint64_t input[RATE_LANES] = {0}; 
    int i;
    for (i = 0; i < RATE_LANES; i++) {
        input[i] = 0xFFFFFFFFFFFFFFFF; 
    }

    absorb_message_block(state, input);
    int allNonZero = 1;
    for (i = RATE_LANES; i < STATE_SIZE; i++) {
        if (state[i] == 0) {
            allNonZero = 0;
            break;
        }
    }

    if (allNonZero) {
        printf("All capacity lanes have at least one nonzero bit.\n");
    } else {
        printf("Not all capacity lanes have at least one nonzero bit.\n");
    }

    return 0;
}


