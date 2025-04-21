#include <stdio.h>
#include "definitions.h"
#include "init.c"
#include "bitboards.c"

int main() {

    AllInit();
    int index = 0;
    U64 playBitBoard = 0ULL;


    for (index = 0; index < 64; index++) {
        printf("index: %d\n", index);
        PrintBitBoard(ClearMask[index]);
        printf("\n");
    }

    SETBIT(playBitBoard, 30);
    PrintBitBoard(playBitBoard);
    printf("\n");

    return 0;
}