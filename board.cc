#include "board.h"

using namespace std;

Board::Board() : board(8, vector<Piece>(8)) {
    for (int ii = 1; ii <= 8; ++ii) {
        for (char jj = 'a'; jj <= 'h'; ++jj) {
            board[ii - 1][int(jj) - 97].setRow(ii);
            board[ii - 1][int(jj) - 97].setCol(jj);            
            board[ii - 1][int(jj) - 97].setKind(boxColor(ii, jj));      
        }
    }
}

Board::Board(Board *boardShot) : board(8, vector<Piece>(8)) {
    for (int ii = 1; ii <= 8; ++ii) {
        for (char jj = 'a'; jj <= 'h'; ++jj) {
            board[ii - 1][int(jj) - 97].setRow(boardShot->get(ii, jj).getRow());
            board[ii - 1][int(jj) - 97].setCol(boardShot->get(ii, jj).getCol());            
            board[ii - 1][int(jj) - 97].setKind(boardShot->get(ii, jj).getKind());      
        }
    }
}

void Board::clearBoard() {
    for (int ii = 1; ii <= 8; ++ii) {
        for (char jj = 'a'; jj <= 'h'; ++jj) {
            board[ii - 1][int(jj) - 97].setRow(ii);
            board[ii - 1][int(jj) - 97].setCol(jj);            
            board[ii - 1][int(jj) - 97].setKind(boxColor(ii, jj));      
        }
    }
}

void Board::printBoard() {
    for (int ii = 0; ii < 8; ++ii) {
        cout << 8 - ii << " ";
        for (int jj = 0; jj < 8; ++jj) {
            cout << board[ii][jj].getKind();
        }
        cout << endl;
    }
    cout << "\n  " << "abcdefgh" << endl;
}

char Board::boxColor(int row, char col) {
    return ((row + (int(col) - 96)) % 2 == 1) ? '-' : ' ';
}

void Board::set(int row, char col, char kind) {
    board[row - 1][int(col) - 97].setKind(kind);
}

void Board::move(int startRow, char startCol, int endRow, char endCol, char kind) {
    set(startRow, startCol, boxColor(startRow, startCol));

    set(endRow, endCol, kind);
}

Piece Board::get(int row, char col) {
    return board[row - 1][int(col) - 97];
}

Piece Board::getKing(char k) {
    for (int ii = 1; ii <= 8; ++ii) {
        for (char jj = 'a'; jj <= 'h'; ++jj) {
            if (board[ii - 1][int(jj) - 97].getKind() == k) {
                return board[ii - 1][int(jj) - 97];
            }
   
        }
    }
}
