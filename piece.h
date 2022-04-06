#ifndef __PIECE_H__
#define __PIECE_H__

#include <string>

using namespace std;

class Piece {
  protected:
    int row;
    char col;
    char kind;

  public:
    Piece() : kind('-'), row(-1), col(-1) {};

    void setKind(char becomes);
    void setRow(int x);
    void setCol(char y);

    char getKind();
    int getRow();
    char getCol();

    bool isValid(int startRow, char startCol, int endRow, char endCol, char endKind);
};

#endif