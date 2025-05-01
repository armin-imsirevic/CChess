#include <stdio.h>
#include "definitions.h"

int CheckBoard(const S_BOARD *pos) {

	int t_piecesNum[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int t_bigPieces[2] = { 0, 0};
	int t_majPieces[2] = { 0, 0};
	int t_minPieces[2] = { 0, 0};
	int t_material[2] = { 0, 0};

	int sq64,t_piece,t_pce_num,sq120,colour,pcount;

	U64 t_pawns[3] = {0ULL, 0ULL, 0ULL};

	t_pawns[WHITE] = pos->pawns[WHITE];
	t_pawns[BLACK] = pos->pawns[BLACK];
	t_pawns[BOTH] = pos->pawns[BOTH];

	// check piece lists
	for(t_piece = whitePawn; t_piece <= blackKing; ++t_piece) {
		for(t_pce_num = 0; t_pce_num < pos->piecesNum[t_piece]; ++t_pce_num) {
			sq120 = pos->pieceList[t_piece][t_pce_num];
			ASSERT(pos->pieces[sq120] == t_piece);
		}
	}

	// check piece count and other counters
	for(sq64 = 0; sq64 < 64; ++sq64) {
		sq120 = SQ120(sq64);
		t_piece = pos->pieces[sq120];
		t_piecesNum[t_piece]++;
		colour = PieceCol[t_piece];
		if( PieceBig[t_piece] == TRUE) t_bigPieces[colour]++;
		if( PieceMin[t_piece] == TRUE) t_minPieces[colour]++;
		if( PieceMaj[t_piece] == TRUE) t_majPieces[colour]++;

		t_material[colour] += PieceVal[t_piece];
	}

	for(t_piece = whitePawn; t_piece <= blackKing; ++t_piece) {
		ASSERT(t_piecesNum[t_piece]==pos->piecesNum[t_piece]);
	}

	// check bitboards count
	pcount = CNT(t_pawns[WHITE]);
	ASSERT(pcount == pos->piecesNum[whitePawn]);
	pcount = CNT(t_pawns[BLACK]);
	ASSERT(pcount == pos->piecesNum[blackPawn]);
	pcount = CNT(t_pawns[BOTH]);
	ASSERT(pcount == (pos->piecesNum[blackPawn] + pos->piecesNum[whitePawn]));

	// check bitboards squares
	while(t_pawns[WHITE]) {
		sq64 = POP(&t_pawns[WHITE]);
		ASSERT(pos->pieces[SQ120(sq64)] == whitePawn);
	}

	while(t_pawns[BLACK]) {
		sq64 = POP(&t_pawns[BLACK]);
		ASSERT(pos->pieces[SQ120(sq64)] == blackPawn);
	}

	while(t_pawns[BOTH]) {
		sq64 = POP(&t_pawns[BOTH]);
		ASSERT( (pos->pieces[SQ120(sq64)] == blackPawn) || (pos->pieces[SQ120(sq64)] == whitePawn) );
	}

	ASSERT(t_material[WHITE]==pos->material[WHITE] && t_material[BLACK]==pos->material[BLACK]);
	ASSERT(t_minPieces[WHITE]==pos->minPieces[WHITE] && t_minPieces[BLACK]==pos->minPieces[BLACK]);
	ASSERT(t_majPieces[WHITE]==pos->majPieces[WHITE] && t_majPieces[BLACK]==pos->majPieces[BLACK]);
	ASSERT(t_bigPieces[WHITE]==pos->bigPieces[WHITE] && t_bigPieces[BLACK]==pos->bigPieces[BLACK]);

	ASSERT(pos->side == WHITE || pos->side == BLACK);
	ASSERT(GeneratePosKey(pos) == pos->posKey);

	ASSERT(pos->enPas==NO_SQ || ( RanksBrd[pos->enPas]==RANK_6 && pos->side == WHITE)
		 || ( RanksBrd[pos->enPas] == RANK_3 && pos->side == BLACK));

	ASSERT(pos->pieces[pos->KingSquares[WHITE]] == whiteKing);
	ASSERT(pos->pieces[pos->KingSquares[BLACK]] == blackKing);

	ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);

	// ASSERT(PceListOk(pos));

	return TRUE;
}

void UpdateListsMaterial(S_BOARD *pos) {

	int piece, sq, index, colour;

	for(index = 0; index < BOARD_SQUARE_NUMBER; ++index) {
		sq = index;
		piece = pos->pieces[index];
		// ASSERT(PceValidEmptyOffbrd(piece));
		if(piece!=OFFBOARD && piece!= EMPTY) {
			colour = PieceCol[piece];
			// ASSERT(SideValid(colour));

		    if( PieceBig[piece] == TRUE) pos->bigPieces[colour]++;
		    if( PieceMin[piece] == TRUE) pos->minPieces[colour]++;
		    if( PieceMaj[piece] == TRUE) pos->majPieces[colour]++;

			pos->material[colour] += PieceVal[piece];

			ASSERT(pos->piecesNum[piece] < 10 && pos->piecesNum[piece] >= 0);

			pos->pieceList[piece][pos->piecesNum[piece]] = sq;
			pos->piecesNum[piece]++;


			if(piece==whiteKing) pos->KingSquares[WHITE] = sq;
			if(piece==blackKing) pos->KingSquares[BLACK] = sq;

			if(piece==whitePawn) {
				SETBIT(pos->pawns[WHITE],SQ64(sq));
				SETBIT(pos->pawns[BOTH],SQ64(sq));
			} else if(piece==blackPawn) {
				SETBIT(pos->pawns[BLACK],SQ64(sq));
				SETBIT(pos->pawns[BOTH],SQ64(sq));
			}
		}
	}
}

int ParseFen(char *fen, S_BOARD *pos) {

	ASSERT(fen!=NULL);
	ASSERT(pos!=NULL);

	int  rank = RANK_8;
    int  file = FILE_A;
    int  piece = 0;
    int  count = 0;
    int  i = 0;
	int  sq64 = 0;
	int  sq120 = 0;

	ResetBoard(pos);

	while ((rank >= RANK_1) && *fen) {
	    count = 1;
		switch (*fen) {
            case 'p': piece = blackPawn; break;
            case 'r': piece = blackRook; break;
            case 'n': piece = blackKnight; break;
            case 'b': piece = blackBishop; break;
            case 'k': piece = blackKing; break;
            case 'q': piece = blackQueen; break;
            case 'P': piece = whitePawn; break;
            case 'R': piece = whiteRook; break;
            case 'N': piece = whiteKnight; break;
            case 'B': piece = whiteBishop; break;
            case 'K': piece = whiteKing; break;
            case 'Q': piece = whiteQueen; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                piece = EMPTY;
                count = *fen - '0';
                break;

            case '/':
            case ' ':
                rank--;
                file = FILE_A;
                fen++;
                continue;

            default:
                printf("FEN error \n");
                return -1;
        }

		for (i = 0; i < count; i++) {
            sq64 = rank * 8 + file;
			sq120 = SQ120(sq64);
            if (piece != EMPTY) {
                pos->pieces[sq120] = piece;
            }
			file++;
        }
		fen++;
	}

	ASSERT(*fen == 'w' || *fen == 'b');

	pos->side = (*fen == 'w') ? WHITE : BLACK;
	fen += 2;

	for (i = 0; i < 4; i++) {
        if (*fen == ' ') {
            break;
        }
		switch(*fen) {
			case 'K': pos->castlePerm |= WHITE_KINGSIDE_CASTLE; break;
			case 'Q': pos->castlePerm |= WHITE_QUEENSIDE_CASTLE; break;
			case 'k': pos->castlePerm |= BLACK_KINGSIDE_CASTLE; break;
			case 'q': pos->castlePerm |= BLACK_QUEENSIDE_CASTLE; break;
			default:	     break;
        }
		fen++;
	}
	fen++;

	ASSERT(pos->castlePerm>=0 && pos->castlePerm <= 15);

	if (*fen != '-') {
		file = fen[0] - 'a';
		rank = fen[1] - '1';

		ASSERT(file>=FILE_A && file <= FILE_H);
		ASSERT(rank>=RANK_1 && rank <= RANK_8);

		pos->enPas = FR2SQ(file,rank);
    }

	pos->posKey = GeneratePosKey(pos);

	UpdateListsMaterial(pos);

	return 0;
}

void ResetBoard(S_BOARD *pos) {

	int index = 0;

	for(index = 0; index < BOARD_SQUARE_NUMBER; ++index) {
		pos->pieces[index] = OFFBOARD;
	}

	for(index = 0; index < 64; ++index) {
		pos->pieces[SQ120(index)] = EMPTY;
	}

	for(index = 0; index < 2; ++index) {
		pos->bigPieces[index] = 0;
		pos->majPieces[index] = 0;
		pos->minPieces[index] = 0;
		pos->material[index] = 0;
		pos->pawns[index] = 0ULL;
	}

	for(index = 0; index < 3; ++index) {
		pos->pawns[index] = 0ULL;
	}

	for(index = 0; index < 13; ++index) {
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
void PrintBoard(const S_BOARD *pos) {

	int sq,file,rank,piece;

	printf("\nGame Board:\n\n");

	for(rank = RANK_8; rank >= RANK_1; rank--) {
		printf("%d  ",rank+1);
		for(file = FILE_A; file <= FILE_H; file++) {
			sq = FR2SQ(file,rank);
			piece = pos->pieces[sq];
			printf("%3c",PieceChar[piece]);
		}
		printf("\n");
	}

	printf("\n   ");
	for(file = FILE_A; file <= FILE_H; file++) {
		printf("%3c",'a'+file);
	}
	printf("\n");
	printf("side:%c\n",SideChar[pos->side]);
	printf("enPas:%d\n",pos->enPas);
	printf("castle:%c%c%c%c\n",
			pos->castlePerm & WHITE_KINGSIDE_CASTLE ? 'K' : '-',
			pos->castlePerm & WHITE_QUEENSIDE_CASTLE ? 'Q' : '-',
			pos->castlePerm & BLACK_KINGSIDE_CASTLE ? 'k' : '-',
			pos->castlePerm & BLACK_QUEENSIDE_CASTLE ? 'q' : '-'
			);
	printf("PosKey:%llX\n",pos->posKey);
}
