#include <stdio.h>
#include "definitions.h"
#include "init.c"
#include "bitboards.c"

int main() {

    AllInit();

    U64 playBitBoard = 0ULL;

    printf("Initial bitboard:\n");

    playBitBoard |= (1ULL << SQ64(D2));
    playBitBoard |= (1ULL << SQ64(D3));
    playBitBoard |= (1ULL << SQ64(D4));

    PrintBitBoard(playBitBoard);

    int count = CNT(playBitBoard);

    printf("Count of bits: %d\n", count);

    int pop = POP(&playBitBoard);
    printf("Popped bit: %d\n", pop);
    printf("Bitboard after pop:\n");
    PrintBitBoard(playBitBoard);
    printf("Count of bits: %d\n", CNT(playBitBoard));

    while (playBitBoard) {
        pop = POP(&playBitBoard);
        printf("Popped bit: %d\n", pop);
        printf("Bitboard after pop:\n");
        PrintBitBoard(playBitBoard);
        printf("Count of bits: %d\n", CNT(playBitBoard));
    }
    printf("Final bitboard:\n");

    return 0;
}