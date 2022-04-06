#ifndef __BOARD_H__
#define __BOARD_H__

#include <string>
#include <vector>
#include <iostream>

#include "piece.h"

using namespace std;

class Board {
  private:
    vector<vector<Piece>> board;
  public:
    Board();
    Board(Board *boardShot);
    void printBoard();
    char boxColor(int row, char col);
    void set(int row, char col, char kind);
    
    // board is dumb, does what it's been told
    void move(int startRow, char startCol, int endRow, char endCol, char kind);
    Piece get(int row, char col);

    Piece getKing(char k);

    void clearBoard();
};

#endif