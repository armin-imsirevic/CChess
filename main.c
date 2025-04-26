#include <stdio.h>
#include "definitions.h"

#define FEN1 "rnbqkbnr/ppp1pppp/8/8/8/8/PPPPP1PP/RNBQKBNR w KQkq - 0 1"
#define FEN2 "rnbqkbnr/ppp2ppp/8/8/8/8/P4PPP/RNBQKBNR w KQkq - 0 1"

int main() {

    AllInit();

    S_BOARD board[1];

    ParseFen(FEN1, board);
    PrintBoard(board);
    board->posKey ^= SideKey;
    ASSERT(CheckBoard(board));

    

    return 0;
}