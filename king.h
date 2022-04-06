#ifndef __KING_H__
#define __KING_H__

#include <string>
#include <iostream>
#include "piece.h"

using namespace std;

class King : Piece {
    public:
        King(Piece *parentPiece);
        bool isValid(int startRow, char startCol, int endRow, char endCol, char endKind);
        bool isValidMove(char endKind);
};

#endif
