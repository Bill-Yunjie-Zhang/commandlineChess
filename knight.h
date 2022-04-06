#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"

using namespace std;

class Knight : Piece {
    public:
        Knight(Piece *parentPiece);
        bool isValid(int startRow, char startCol, int endRow, char endCol, char endKind);
};

#endif