#include "definitions.h"

int SqOnBoard(const int sq) {
    return FilesBrd[sq] == OFFBOARD ? FALSE : TRUE;
}

int SideValid(const int side) {
    return (side == WHITE || side == BLACK) ? TRUE : FALSE;
}

int PieceValid(const int piece) {
    return (piece >= whitePawn && piece <= blackKing) ? TRUE : FALSE;
}

int PieceValidEmpty(const int piece) {
    return (piece >= EMPTY && piece <= blackKing) ? TRUE : FALSE;
}

int FileRankValid(const int fr) {
    return (fr >= 0 && fr <= 7) ? TRUE : FALSE;
}