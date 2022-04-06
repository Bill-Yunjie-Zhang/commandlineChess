#ifndef __ROOK_H__
#define __ROOK_H__

#include <string>
#include <iostream>
#include "piece.h"

using namespace std;

class Rook : Piece {
    public:
        Rook(Piece *parentPiece);
        bool isValid(int startRow, char startCol, int endRow, char endCol, char endKind);
        bool isValidMove(char endKind);
};

#endif
