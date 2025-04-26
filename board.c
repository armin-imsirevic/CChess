#include <stdio.h>
#include "definitions.h"

int UpdateListsMaterial(S_BOARD *pos) {
    int piece, sq, index, color; 

    for (index = 0; index < BOARD_SQUARE_NUMBER; ++index) {
        sq = index;
        piece = pos->pieces[index];
        if (piece != OFFBOARD && piece != EMPTY) {
            color = PieceCol[piece];

            if (PieceBig[piece] == TRUE) {
                pos->bigPieces[color]++;
            }
            if (PieceMaj[piece] == TRUE) {
                pos->majPieces[color]++;
            }
            if (PieceMin[piece] == TRUE) {
                pos->minPieces[color]++;
            }

            pos->material[color] += PieceVal[piece];

            pos->pieceList[piece][pos->piecesNum[piece]] = sq;
            pos->piecesNum[piece]++;

            if (piece == whiteKing) pos->KingSquares[WHITE] = sq;
            if (piece == blackKing) pos->KingSquares[BLACK] = sq;
        }
    }

    return 0;
}

int ParseFen(char *fen, S_BOARD *pos) {
    ASSERT(fen != NULL);
    ASSERT(pos != NULL);
    int rank = RANK_8;
    int file = FILE_A;
    int piece = 0;
    int count = 0;
    int i = 0;
    int sq64 = 0;
    int sq120 = 0;

    ResetBoard(pos);

    while (rank >= RANK_1 && *fen) {
        count = 1;
        switch (*fen)
        {
            case 'p': piece = blackPawn; break;
            case 'r': piece = blackRook; break;
            case 'n': piece = blackKnight; break;
            case 'b': piece = blackBishop; break;
            case 'q': piece = blackQueen; break;
            case 'k': piece = blackKing; break;
            case 'P': piece = whitePawn; break;
            case 'R': piece = whiteRook; break;
            case 'N': piece = whiteKnight; break;
            case 'B': piece = whiteBishop; break;
            case 'Q': piece = whiteQueen; break;
            case 'K': piece = whiteKing; break;
            case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8':
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
                printf("Invalid character: %c\n", *fen);
                return -1;
        }

        for (i = 0; i < count; i++) {
            sq64 = (rank * 8) + file;
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

    for (int i = 0; i < 4; i++) {
        if (*fen == ' ') {
            break;
        }
        switch (*fen) {
            case 'K': pos->castlePerm |= BLACK_KINGSIDE_CASTLE; break;
            case 'Q': pos->castlePerm |= BLACK_QUEENSIDE_CASTLE; break;
            case 'k': pos->castlePerm |= WHITE_KINGSIDE_CASTLE; break;
            case 'q': pos->castlePerm |= WHITE_QUEENSIDE_CASTLE; break;
            default: break;
        }
        fen++;
    }
    fen++;

    ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);

    if (*fen != '-') {
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        ASSERT(file >= FILE_A && file <= FILE_H);
        ASSERT(rank >= RANK_1 && rank <= RANK_8);

        pos->enPas = FILE_RANK_TO_SQ(file, rank);        
    }

    pos->posKey = GeneratePosKey(pos);

    return 0;
}

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

void PrintBoard(const S_BOARD *pos) {
    int sq, file, rank, piece;

    printf("\nGame Board:\n");

    for (rank = RANK_8; rank >= RANK_1; rank--) {
        printf("%d  ", rank + 1);
        for (file = FILE_A; file <= FILE_H; file++) {
            sq = FILE_RANK_TO_SQ(file, rank);
            piece = pos->pieces[sq];
            printf("%3c ", PieceChar[piece]);
        }
        printf("\n");
    }

    printf("\n   ");
    for (file = FILE_A; file <= FILE_H; file++) {
        printf("%3c ", 'a' + file);
    }
    printf("\n");
    printf("side:%c\n", SideChar[pos->side]);
    printf("enPas:%d\n", pos->enPas);
    printf("castle:%c%c%c%c\n",
        pos->castlePerm & WHITE_KINGSIDE_CASTLE ? 'K' : '-',
        pos->castlePerm & WHITE_QUEENSIDE_CASTLE ? 'Q' : '-',
        pos->castlePerm & BLACK_KINGSIDE_CASTLE ? 'k' : '-',
        pos->castlePerm & BLACK_QUEENSIDE_CASTLE ? 'q' : '-');
    printf("PosKey:%llX\n", pos->posKey);
    
}