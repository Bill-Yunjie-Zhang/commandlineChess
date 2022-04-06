#include "bishop.h"

Bishop::Bishop(Piece *parentPiece) {
    row = parentPiece->getCol();
    col = parentPiece->getRow();
    kind = parentPiece->getKind();
}

bool Bishop::isValid(int startRow, char startCol, int endRow, char endCol, char endKind) {
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
        }
        
        return false;
    }

    return false;
}

bool Bishop::isValidMove(char endKind) {
    return endKind == ' ' || endKind == '-';
}