#include "knight.h"
#include <iostream>

Knight::Knight(Piece *parentPiece) {
    row = parentPiece->getCol();
    col = parentPiece->getRow();
    kind = parentPiece->getKind();
}

bool Knight::isValid(int startRow, char startCol, int endRow, char endCol, char endKind) {
    bool isSameSide = true;

    if (kind >= 65 && kind <= 90) {
        if (endKind >= 97 && endKind <= 122) {
            isSameSide = false;
        }
    } else if (endKind >= 97 && endKind <= 122) {
        if (kind >= 65 && kind <= 90) {
            isSameSide = false;
        }
    }

    if ((endKind == ' ' || endKind == '-') || !isSameSide) {
        if ((startRow + 2 == endRow && startCol + 1 == endCol) ||
            (startRow + 2 == endRow && startCol - 1 == endCol) ||
            (startRow - 2 == endRow && startCol + 1 == endCol) ||
            (startRow - 2 == endRow && startCol - 1 == endCol) ||
        
            (startRow + 1 == endRow && startCol + 2 == endCol) ||
            (startRow + 1 == endRow && startCol - 2 == endCol) ||
            (startRow - 1 == endRow && startCol + 2 == endCol) ||
            (startRow - 1 == endRow && startCol - 2 == endCol)) {
            return true;
        } else {
            return false;
        }
    }

    return false;
}