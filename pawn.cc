#include <iostream>

#include "pawn.h"

Pawn::Pawn(Piece *parentPiece) {
    row = parentPiece->getCol();
    col = parentPiece->getRow();
    kind = parentPiece->getKind();

    isEnd = (row == 1 || row == 8) ? true : false;
}

bool Pawn::isValid(int startRow, char startCol, int endRow, char endCol, char endKind) {
    // whether the Pawn has moved or not
    bool moved = false;
    bool isOppose = true;

    if (kind == 'p') {
        isOppose = false;
        if (startRow != 2) {
            moved = true;
        }
    }

    if (kind == 'P') {
        if (startRow != 7) {
            moved = true;
        }
    }

    // move legal
    if (startCol == endCol) {
        if (endKind == ' ' || endKind == '-') {
            if (isOppose) {
                if (startRow - 1 == endRow) {
                    return true;
                }

                if (!moved && startRow - 2 == endRow) {
                    return true;
                }
            } else {
                if (startRow + 1 == endRow) {
                    return true;
                }

                if (!moved && startRow + 2 == endRow) {
                    return true;
                }
            }
        } else {
            return false;
        }
    }

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
    
    // eat legal
    if ((endKind != ' ' || endKind != '-') || !isSameSide) {
        if (isOppose) {
            if (startRow - 1 == endRow) {
                if (startCol + 1 == endCol || startCol - 1 == endCol) {
                    return true;
                }
            }
        } else {
            if (startRow + 1 == endRow) {
                if (startCol + 1 == endCol || startCol - 1 == endCol) {
                    return true;
                }
            }
        }
    }

    return false;
}