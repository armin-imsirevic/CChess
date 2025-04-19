#include <stdio.h>
#include "definitions.h"
#include "init.c"
#include "bitboards.c"

int main() {

    AllInit();

    U64 playBitBoard = 0ULL;

    printf("Initial bitboard:\n");
    PrintBitBoard(playBitBoard);

    playBitBoard |= (1ULL << SQ64(D2));
    printf("After placing a piece on D2:\n");
    PrintBitBoard(playBitBoard);

    playBitBoard |= (1ULL << SQ64(G2));
    printf("After placing a piece on G2:\n");
    PrintBitBoard(playBitBoard);

    return 0;
}