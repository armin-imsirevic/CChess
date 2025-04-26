#ifndef DEFS_H
#define DEFS_H

#include "stdlib.h"

// #define DEBUG
#ifndef DEBUG
#define ASSERT(x)
#else
#define ASSERT(x) if(!(x)) { printf("Assertion failed: %s, file %s, line %d\n", #x, __FILE__, __LINE__); exit(1); }
#endif

typedef unsigned long long U64;

#define NAME "Chess Engine 1.0"
#define BOARD_SQUARE_NUMBER 120

#define MAX_GAME_MOVES 2048

#define START_FEN "rnbqkb1r/pppppppp/8/8/8/8/PPPPPPPP/RNBQKB1R w KQkq - 0 1"

enum { EMPTY, whitePawn, whiteKnight, whiteBishop, whiteRook, whiteQueen, whiteKing,
    blackPawn, blackKnight, blackBishop, blackRook, blackQueen, blackKing };
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H,
    FILE_NONE };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, 
    RANK_NONE };

enum { WHITE, BLACK, BOTH };
enum {
    A1 = 21, B1 = 22, C1 = 23, D1 = 24, E1 = 25, F1 = 26, G1 = 27, H1 = 28,
    A2 = 31, B2 = 32, C2 = 33, D2 = 34, E2 = 35, F2 = 36, G2 = 37, H2 = 38,
    A3 = 41, B3 = 42, C3 = 43, D3 = 44, E3 = 45, F3 = 46, G3 = 47, H3 = 48,
    A4 = 51, B4 = 52, C4 = 53, D4 = 54, E4 = 55, F4 = 56, G4 = 57, H4 = 58,
    A5 = 61, B5 = 62, C5 = 63, D5 = 64, E5 = 65, F5 = 66, G5 = 67, H5 = 68,
    A6 = 71, B6 = 72, C6 = 73, D6 = 74, E6 = 75, F6 = 76, G6 = 77, H6 = 78,
    A7 = 81, B7 = 82, C7 = 83, D7 = 84, E7 = 85, F7 = 86, G7 = 87, H7 = 88,
    A8 = 91, B8 = 92, C8 = 93, D8 = 94, E8 = 95, F8 = 96, G8 = 97, H8 = 98, NO_SQ, OFFBOARD
};

enum {
    FALSE,
    TRUE
};

enum {
    WHITE_KINGSIDE_CASTLE = 1, WHITE_QUEENSIDE_CASTLE = 2, 
    BLACK_KINGSIDE_CASTLE = 4, BLACK_QUEENSIDE_CASTLE = 8
};

typedef struct {
    int move;
    int castlePerm;
    int enPas;
    U64 posKey;
} S_UNDO;

typedef struct {
    int pieces[BOARD_SQUARE_NUMBER];
    U64 pawns[3];
    int KingSquares[2];

    int side;
    int enPas;
    int fiftyMove;
    int ply;
    int hisPly;

    int castlePerm;

    U64 posKey;
    
    int piecesNum[13];
    int bigPieces[2];
    int majPieces[2];
    int minPieces[2];
    int material[2];

    int pieceList[13][10];

    S_UNDO history[MAX_GAME_MOVES];
} S_BOARD;

// Macros
#define FILE_RANK_TO_SQ(file, rank) ( (21 + (file)) + (rank) * 10 )
#define SQ64(sq120) (Sq120To64[(sq120)])
#define SQ120(sq64) (Sq64To120[(sq64)])
#define POP(b) PopBit(b)
#define CNT(b) CountBits(b)
#define CLRBIT(bb, sq) (bb &= ClearMask[sq])
#define SETBIT(bb, sq) (bb |= SetMask[sq])

// Global variables
extern int Sq120To64[BOARD_SQUARE_NUMBER];
extern int Sq64To120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];
extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];
extern char PieceChar[];
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];

extern int PieceBig[13];
extern int PieceMaj[13];
extern int PieceMin[13];
extern int PieceVal[13];
extern int PieceCol[13];

// Global functions
extern void AllInit();

extern void PrintBitBoard(U64 bitBoard);
extern int CountBits(U64 b);
extern int PopBit(U64 *bb);

extern U64 GeneratePosKey(const S_BOARD *pos);
extern void ResetBoard(S_BOARD *pos);
extern int ParseFen(char *fen, S_BOARD *pos);
extern void PrintBoard(const S_BOARD *pos);
extern int UpdateListsMaterial(S_BOARD *pos);

#endif