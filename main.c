#include <stdio.h>
#include "definitions.h"

#define FEN1 "8/3q1p2/8/5P2/4Q3/8/8/8 w - - 0 2"
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1P/PPPBBPP1/R3K2R w KQkq - 0 1"

void ShowSqAtBySide(const int side, const S_BOARD *pos) {
    int rank = 0;
    int file = 0;
    int sq = 0;

    printf("\n\nSquares attacked by:%c\n", SideChar[side]);
    for(rank = RANK_8; rank >= RANK_1; --rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq = FR2SQ(file, rank);
            if(SqAttacked(sq, side, pos) == TRUE) {
                printf("x");
            } else {
                printf("-");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

int main() {

    AllInit();

    S_BOARD board[1];

    ParseFen(FEN1, board);
    PrintBoard(board);
    // board->posKey ^= SideKey;
    // ASSERT(CheckBoard(board));

    printf("\n\nWhite attacks:\n");
    ShowSqAtBySide(WHITE, board);


    printf("\n\nBlack attacks:\n");
    ShowSqAtBySide(BLACK, board);
    printf("\n\n");

    

    return 0;
}