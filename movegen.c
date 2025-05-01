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

int LoopSlidePiece[8] = {
    whiteBishop, whiteRook, whiteQueen, 0, blackBishop, blackRook, blackQueen, 0
};

int LoopSlideIndex[2] = {
    0, 4,
};

int LoopNonSlidePiece[6] = {
    whiteKnight, whiteKing, 0, blackKnight, blackKing, 0
};
int LoopNonSlideIndex[3] = {
    0, 3
};



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

void AddWhitePawnCapMove(const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list) {
    ASSERT(PieceValidEmpty(cap));
    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));
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
    ASSERT(PieceValidEmpty(cap));
    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));
    if (RanksBrd[from] == RANK_7) {
        AddQuiteMove(pos, MOVE(from, to, EMPTY, whiteQueen, 0), list);
        AddQuiteMove(pos, MOVE(from, to, EMPTY, whiteRook, 0), list);
        AddQuiteMove(pos, MOVE(from, to, EMPTY, whiteBishop, 0), list);
        AddQuiteMove(pos, MOVE(from, to, EMPTY, whiteKnight, 0), list);
    } else {
        AddQuiteMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
    }
}

void AddBlackPawnCapMove(const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list) {
    ASSERT(PieceValidEmpty(cap));
    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));
    if (RanksBrd[from] == RANK_2) {
        AddCaptureMove(pos, MOVE(from, to, cap, blackQueen, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, blackRook, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, blackBishop, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, blackKnight, 0), list);
    } else {
        AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
    }
}

void AddBlackPawnMove(const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list) {
    ASSERT(PieceValidEmpty(cap));
    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));
    if (RanksBrd[from] == RANK_2) {
        AddQuiteMove(pos, MOVE(from, to, EMPTY, blackQueen, 0), list);
        AddQuiteMove(pos, MOVE(from, to, EMPTY, blackRook, 0), list);
        AddQuiteMove(pos, MOVE(from, to, EMPTY, blackBishop, 0), list);
        AddQuiteMove(pos, MOVE(from, to, EMPTY, blackKnight, 0), list);
    } else {
        AddQuiteMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
    }
}

void GenerateAllMoves(const S_BOARD *pos, S_MOVELIST *list) {
    ASSERT(CheckBoard(pos));

    list->count = 0;

    int pce = 0;
    int side = pos->side;
    int sq = 0;
    int t_sq = 0;
    int piecesNum = 0;
    int dir = 0;
    int index = 0;
    int pieceIndex = 0;

    printf("\n\nSide: %d\n", side);

    if (side == WHITE) {
        for (piecesNum = 0; piecesNum < pos->piecesNum[whitePawn]; ++piecesNum) {
            sq = pos->pieceList[whitePawn][piecesNum];
            ASSERT(SqOnBoard(sq));

            if (pos->pieces[sq + 10] == EMPTY) {
                AddWhitePawnMove(pos, sq, sq + 10, EMPTY, list);
                if (RanksBrd[sq] == RANK_7 && pos->pieces[sq + 20] == EMPTY) {
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
        for (piecesNum = 0; piecesNum < pos->piecesNum[blackPawn]; ++piecesNum) {
            sq = pos->pieceList[blackPawn][piecesNum];
            ASSERT(SqOnBoard(sq));

            if (pos->pieces[sq - 10] == EMPTY) {
                AddBlackPawnMove(pos, sq, sq - 10, EMPTY, list);
                if (RanksBrd[sq] == RANK_2 && pos->pieces[sq - 20] == EMPTY) {
                    AddQuiteMove(pos, MOVE(sq, sq - 20, EMPTY, EMPTY, MFLAGPS), list);
                }
            }

            if (!SQOFFBOARD(sq - 9) && PieceCol[pos->pieces[sq - 9]] == WHITE) {
                AddBlackPawnCapMove(pos, sq, sq - 9, pos->pieces[sq - 9], list);
            }

            if (!SQOFFBOARD(sq - 11) && PieceCol[pos->pieces[sq - 11]] == WHITE) {
                AddBlackPawnCapMove(pos, sq, sq - 11, pos->pieces[sq - 11], list);
            }

            if (sq - 9 == pos->enPas) {
                AddCaptureMove(pos, MOVE(sq, sq - 9, EMPTY, EMPTY, 0), list);
            }

            if (sq - 11 == pos->enPas) {
                AddCaptureMove(pos, MOVE(sq, sq - 11, EMPTY, EMPTY, 0), list);
            }
        }
    }

    pieceIndex = LoopSlideIndex[side];
    pce = LoopSlidePiece[pieceIndex++];
    while (pce != 0) {
        ASSERT(PieceValid(pce));
        printf("sliders pceIndex:%d pce: %d\n", pieceIndex, pce);

        pce = LoopSlidePiece[pieceIndex++];
    }

    pieceIndex = LoopNonSlideIndex[side];
    pce = LoopNonSlidePiece[pieceIndex++];
    while (pce != 0) {
        ASSERT(PieceValid(pce));
        printf("non-sliders pceIndex:%d pce: %d\n", pieceIndex, pce);

        pce = LoopNonSlidePiece[pieceIndex++];
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