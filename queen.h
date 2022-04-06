#ifndef __QUEEN_H__
#define __QUEEN_H__

#include <string>
#include <iostream>
#include "piece.h"

using namespace std;

class Queen : Piece {
    public:
        Queen(Piece *parentPiece);
        bool isValid(int startRow, char startCol, int endRow, char endCol, char endKind);
        bool isValidMove(char endKind);
};

#endif
