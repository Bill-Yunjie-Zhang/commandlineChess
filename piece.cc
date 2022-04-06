#include "piece.h"

using namespace std;

void Piece::setKind(char k) {
    kind = k;
}

void Piece::setRow(int x) {
    row = x;
}

void Piece::setCol(char y) {
    col = y;
}

char Piece::getKind() {
    return kind;
}

int Piece::getRow() {
    return row;
}

char Piece::getCol() {
    return col;
}