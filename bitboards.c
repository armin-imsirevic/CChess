#include <stdio.h>
#include "definitions.h"

void PrintBitBoard(U64 bitBoard) {
    U64 shiftMe = 1ULL;

    int rank = 0;
    int file = 0;
    int square = 0;
    int square64 = 0;

    printf("\n");
    for(rank = RANK_8; rank >= RANK_1; --rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            square = FILE_RANK_TO_SQ(file, rank); // Convert to 120
            square64 = SQ64(square); // Convert to 64
            if (bitBoard & (shiftMe << square64)) {
                printf("X");
            } else {
                printf("-");
            }
        }
        printf("\n");
    }
    printf("\n");
}