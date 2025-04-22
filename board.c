#include <stdio.h>
#include "definitions.h"

void ResetBoard(S_BOARD *pos) {
    int index = 0;

    for (index = 0; index < BOARD_SQUARE_NUMBER; ++index) {
        pos->pieces[index] = OFFBOARD;
    }

    for (index = 0; index < 64; ++index) {
        pos->pawns[SQ120(index)] = EMPTY;
    }

    for (index = 0; index < 3; ++index) {
        pos->bigPieces[index] = 0;
        pos->majPieces[index] = 0;
        pos->minPieces[index] = 0;
        pos->pawns[index] = 0ULL;
    }

    for (index = 0; index < 13; ++index) {
        pos->piecesNum[index] = 0;
    }

    pos->KingSquares[WHITE] = pos->KingSquares[BLACK] = NO_SQ;

    pos->side = BOTH;
    pos->enPas = NO_SQ;
    pos->fiftyMove = 0;

    pos->ply = 0;
    pos->hisPly = 0;

    pos->castlePerm = 0;

    pos->posKey = 0ULL;
}

