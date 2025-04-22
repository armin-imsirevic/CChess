#include "definitions.h"

U64 GeneratePosKey(const S_BOARD *pos) {
    int sq = 0;
    U64 finalKey = 0;
    int piece = EMPTY;

    for (sq = 0; sq < BOARD_SQUARE_NUMBER; ++sq) {
        piece = pos->pieces[sq];
        if (piece != NO_SQ && piece != EMPTY) {
            ASSERT(piece >= whitePawn && piece < blackKing);
            finalKey ^= PieceKeys[piece][sq];
        }
    }

    if (pos->side == WHITE) {
        finalKey ^= SideKey;
    }

    if (pos->enPas != NO_SQ) {
        ASSERT(pos->enPas >= A1 && pos->enPas < BOARD_SQUARE_NUMBER);
        finalKey ^= PieceKeys[EMPTY][pos->enPas];
    }

    ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);

    finalKey ^= CastleKeys[pos->castlePerm];

    return finalKey;
}