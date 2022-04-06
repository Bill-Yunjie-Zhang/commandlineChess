#ifndef __GAME_H__
#define __GAME_H__

#include <string>
#include <vector>
#include <iostream>

#include "board.h"
#include "player.h"
#include "piece.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"

using namespace std;

class Game {
  private:
    int turn;
    bool isCheckMate;
    Board gameBoard;
    vector<Player> playerList;
    vector<Board> recording;
  public:
    bool isOver;
    bool isSetUp;

    Game();
    void printGame();
    void newGame();

    bool checkTurn(char kind);
    bool checkMove(int startRow, char startCol, int endRow, char endCol);
    
    bool checkCheckMate();

    bool checkPawnMove(Piece startPiece, Piece endPiece);
    bool checkEnPassant(int startRow, char startCol, int endRow, char endCol, char startKind);
    bool checkQueenMove(Piece startPiece, Piece endPiece);
    bool checkRookMove(Piece startPiece, Piece endPiece);
    bool checkKnightMove(Piece startPiece, Piece endPiece);
    bool checkBishopMove(Piece startPiece, Piece endPiece);
    bool checkKingMove(Piece startPieve, Piece endPiece);

    void handleMove(string start, string finish);
    void move(int startRow, char startCol, int endRow, char endCol);

    void moveMultiple(int startRow, char startCol, int endRow, char endCol);
    void setPlayer(int num, bool isMachine);
    
    void handleSetUpPlus(char pieceKind, string position);
    void handleSetUpMinus(string position);
    void handleSetUpEquals(string color);
    bool checkSetUp();

    Player getTurn();
    Player getPlayer(int index);

    void moveAi(int level);
    bool checkEat(int row, char col);

    void randomMove(int id);
    void handleRegret();
    void castling(int startRow, char startCol, int endRow, char endCol, char endKind);
};

#endif