// init.c 

#include "definitions.h"

int Sq120To64[BOARD_SQUARE_NUMBER];
int Sq64To120[64];

void InitSq120To64() {
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;

    for(index = 0; index < BOARD_SQUARE_NUMBER; ++index) {
        Sq120To64[index] = 65;
    }

    for(index = 0; index < 64; ++index) {
        Sq64To120[index] = 120;
    }

    for(rank = RANK_1; rank <= RANK_8; ++rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq = FILE_RANK_TO_SQ(file, rank);
            Sq120To64[sq] = sq64;
            Sq64To120[sq64] = sq;
            sq64++;
        }
    }
}

void AllInit() {
    InitSq120To64();
}
