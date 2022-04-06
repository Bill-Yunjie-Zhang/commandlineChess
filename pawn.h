#ifndef __PAWN_H__
#define __PAWN_H__

#include "piece.h"

using namespace std;

class Pawn : Piece {
    private:
        bool isEnd;
    
    public:
        Pawn(Piece *parentPiece);
        bool isValid(int startRow, char startCol, int endRow, char endCol, char endKind);
};

#endif