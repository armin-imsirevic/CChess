#include <stdio.h>
#include "definitions.h"

// #define FEN1 "8/3q1p2/8/5P2/4Q3/8/8/8 w - - 0 2"
// #define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq c6 0 2"
// #define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"
// #define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1P/PPPBBPP1/R3K2R w KQkq - 0 1"
#define PAWNMOVES "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"

// void PrintBin(int move) {
//     int index = 0;
//     printf("Binary: \n");

//     for (index = 27; index >= 0; index--) {
//         if (1<<index & move) {
//             printf("1");
//         } else {
//             printf("0");
//         }
//         if (index != 28 && index % 4 == 0) {
//             printf(" ");
//         }
//     }
//     printf("\n");
// }

int main() {

    AllInit();

    S_BOARD board[1];

    ParseFen(PAWNMOVES, board);
    PrintBoard(board);

    S_MOVELIST list[1];

    GenerateAllMoves(board, list);

    PrintMoveList(list);

    return 0;
}