#include <stdio.h>
#include "definitions.h"
#include "init.c"

int main() {

    AllInit();

    for (int i = 0; i < BOARD_SQUARE_NUMBER; ++i) {
        if (i % 10 == 0) {
            printf("\n");
        }
        printf("%5d", Sq120To64[i]);
    }

    printf("\n");
    printf("\n");
    for (int i = 0; i < 64; ++i) {
        if (i % 8 == 0) {
            printf("\n");
        }
        printf("%5d", Sq64To120[i]);
    }
    return 0;
}