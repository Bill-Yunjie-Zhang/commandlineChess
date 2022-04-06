#include "queen.h"

Queen::Queen(Piece *parentPiece) {
    row = parentPiece->getCol();
    col = parentPiece->getRow();
    kind = parentPiece->getKind();
}

bool Queen::isValid(int startRow, char startCol, int endRow, char endCol, char endKind) {
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
        if (startRow - endRow == int(startCol) - int(endCol)) {
           return true;
        } else if (startRow - endRow == - int(startCol) + int(endCol)) {
            return true;
        } else if (startRow == endRow) {
            return true;
        } else if (startCol == endCol) {
            return true;
        }
        return false;
    }

    return false;
}

bool Queen::isValidMove(char endKind) {
    return endKind == ' ' || endKind == '-';
}