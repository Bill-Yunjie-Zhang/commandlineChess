#ifndef __BISHOP_H__
#define __BISHOP_H__

#include <string>
#include <iostream>
#include "piece.h"

using namespace std;

class Bishop : Piece {
    public:
        Bishop(Piece *parentPiece);
        bool isValid(int startRow, char startCol, int endRow, char endCol, char endKind);
        bool isValidMove(char endKind);
};

#endif