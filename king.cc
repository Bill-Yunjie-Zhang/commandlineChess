#include "king.h"
#include <iostream>

King::King(Piece *parentPiece) {
    row = parentPiece->getCol();
    col = parentPiece->getRow();
    kind = parentPiece->getKind();
}

bool King::isValid(int startRow, char startCol, int endRow, char endCol, char endKind) {
    // cout << "entering King::isValid()" << endl;

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
        if ((startRow + 1 == endRow) || (startRow - 1 == endRow) ||
            (startCol + 1 == endCol) || (startCol - 1 == endCol)) {
            return true;
        } else {
            return false;
        }
    }

    return false;
}
