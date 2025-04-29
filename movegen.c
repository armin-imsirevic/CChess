#include "definitions.h"
#include "stdio.h"

#define MOVE(f, t, ca, pro, fl) (\
    ( (f) ) | \
    ( (t) << 7 ) | \
    ( (ca) << 14 ) | \
    ( (pro) << 20 ) | \
    ( (fl) ) \
)
#define SQOFFBOARD(sq) (FilesBrd[sq] == OFFBOARD)

void AddQuiteMove(const S_BOARD *pos, int move, S_MOVELIST *list) {
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

void AddCaptureMove(const S_BOARD *pos, int move, S_MOVELIST *list) {
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

void AddEnPassantMove(const S_BOARD *pos, int move, S_MOVELIST *list) {
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

void GenerateAllMoves(const S_BOARD *pos, S_MOVELIST *list) {
    ASSERT(CheckBoard(pos));

    list->count = 0;

    int pce = 0;
    int side = pos->side;
    int sq = 0;
    int t_sq = 0;
    int piecesNum = 0;

    if (side == WHITE) {
        for (piecesNum = 0; piecesNum < pos->piecesNum[whitePawn]; ++piecesNum) {
            sq = pos->pieceList[whitePawn][piecesNum];
            ASSERT(SqOnBoard(sq));

            if (pos->pieces[sq + 10] == EMPTY) {
                AddWhitePawnMove(pos, sq, sq + 10, EMPTY, list);
                if (RanksBrd[sq] == RANK_2 && pos->pieces[sq + 20] == EMPTY) {
                    AddQuiteMove(pos, MOVE(sq, sq + 20, EMPTY, EMPTY, MFLAGPS), list);
                }
            }

            if (!SQOFFBOARD(sq + 9) && PieceCol[pos->pieces[sq + 9]] == BLACK) {
                AddWhitePawnCapMove(pos, sq, sq + 9, pos->pieces[sq + 9], list);
            }

            if (!SQOFFBOARD(sq + 11) && PieceCol[pos->pieces[sq + 11]] == BLACK) {
                AddWhitePawnCapMove(pos, sq, sq + 11, pos->pieces[sq + 11], list);
            }

            if (sq + 9 == pos->enPas) {
                AddCaptureMove(pos, MOVE(sq, sq + 9, EMPTY, EMPTY, 0), list);
            }

            if (sq + 11 == pos->enPas) {
                AddCaptureMove(pos, MOVE(sq, sq + 11, EMPTY, EMPTY, 0), list);
            }
        }
    } else {

    }
}

void AddWhitePawnCapMove(const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list) {
    if (RanksBrd[from] == RANK_7) {
        AddCaptureMove(pos, MOVE(from, to, cap, whiteQueen, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, whiteRook, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, whiteBishop, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, whiteKnight, 0), list);
    } else {
        AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
    }
}

void AddWhitePawnMove(const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list) {
    if (RanksBrd[from] == RANK_7) {
        AddQuiteMove(pos, MOVE(from, to, EMPTY, whiteQueen, 0), list);
        AddQuiteMove(pos, MOVE(from, to, EMPTY, whiteRook, 0), list);
        AddQuiteMove(pos, MOVE(from, to, EMPTY, whiteBishop, 0), list);
        AddQuiteMove(pos, MOVE(from, to, EMPTY, whiteKnight, 0), list);
    } else {
        AddQuiteMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
    }
}

void PrintMoveList(const S_MOVELIST *list) {
	int index = 0;
	int score = 0;
	int move = 0;
	printf("MoveList:\n");

	for(index = 0; index < list->count; ++index) {

		move = list->moves[index].move;
		score = list->moves[index].score;

		printf("Move:%d > %s (score:%d)\n",index+1,PrintMove(move),score);
	}
	printf("MoveList Total %d Moves:\n\n",list->count);
}