#include "game.h"

Game::Game() : playerList(2) {
    isOver = false;
    turn = 0;
    isCheckMate = false;
    isSetUp = false;

    playerList[0].setColor("white");
    playerList[0].setId(0);
    playerList[0].setBot(false);

    playerList[1].setColor("black");
    playerList[1].setId(1);
    playerList[1].setBot(false);
}

void Game::printGame() {
    gameBoard.printBoard();
}

void Game::castling(int startRow, char startCol, int endRow, char endCol, char endKind) {
    
}

void Game::newGame() {
    turn = 0;
    isCheckMate = false;
    recording.clear();

    gameBoard.clearBoard();

    string blackBaseRow = "rnbqkbnr";
    string whiteBaseRow = "RNBQKBNR";
    
    for (char ii = 'a'; ii <= 'h'; ++ii) {
        gameBoard.set(1, ii, blackBaseRow.at(int(ii) - 97));
        gameBoard.set(2, ii, 'p');   

        gameBoard.set(8, ii, whiteBaseRow.at(int(ii) - 97));
        gameBoard.set(7, ii, 'P');     
    }
}

bool Game::checkBishopMove(Piece startPiece, Piece endPiece) {

    int startRow = startPiece.getRow();
    char startCol = startPiece.getCol();
    int endRow = endPiece.getRow();
    char endCol = endPiece.getCol();

    Bishop thisBishop = Bishop(&startPiece);
    char endKind = endPiece.getKind();

    int x = 0;
    int y = 0;

    if (thisBishop.isValid(startRow, startCol, endRow, endCol, endKind)) {

        if (endRow - startRow > 0) {
            y = 1;
        } else if (endRow - startRow < 0) {
            y = -1;
        }
        
        if (int(endCol) - int(startCol) > 0) {
            x = 1;
        } else if (int(endCol) - int(startCol) < 0) {
            x = -1;
        }
    }

    int ii = startRow + y;
    char jj = startCol + x;

    while (ii != endRow || jj != endCol) {
        char routeKind = gameBoard.get(ii, jj).getKind();

        if (!thisBishop.isValidMove(routeKind)) {
            return false;
        }

        ii += y;
        jj += x;
    }

    return true;
}

bool Game::checkKingMove(Piece startPiece, Piece endPiece) {
    int startRow = startPiece.getRow();
    char startCol = startPiece.getCol();
    int endRow = endPiece.getRow();
    char endCol = endPiece.getCol();

    King thisKing = King(&startPiece);
    char endKind = endPiece.getKind();
    
    // if ((startRow == endRow) && (startRow == 1 || startRow == 8)) {

    //     bool blocked = false;

    //     cout << endKind << endl;
    //     if (endKind != ' ' && endKind != '-') {
    //         blocked = true;
    //     }

    //     int x1 = 0;
    //     char col = startCol + 1;

    //     cout << "col: " << col << endl;
    //     if (int(endCol) - int(startCol) == 2 || int(endCol) - int(startCol) == -2) {
    //         x1 = (int(endCol) - int(startCol)) / 2;
    //     }

    //     while (col < 'h' && col > 'a') {
    //         cout << gameBoard.get(startRow, col).getKind() << endl;
    //         cout << gameBoard.boxColor(startRow, col) << endl;
    //         if (gameBoard.get(startRow, col).getKind() != gameBoard.boxColor(startRow, col)) {
    //             blocked = true;
    //             break;
    //         }

    //         if (x1 == 1) {
    //             col += 1;
    //         } else if (x1 == -1) {
    //             col -= 1;
    //         }
    //     }

    //     if (!isCheckMate && !blocked) {            
    //         if (startRow == 8) {
    //             gameBoard.set(startRow, startCol + x1, 'K');
    //             bool firstStep = checkCheckMate();
    //             gameBoard.set(startRow, startCol + x1, gameBoard.boxColor(startRow, startCol + x1));
    //             gameBoard.set(startRow, startCol + 2 * x1, 'K');
    //             bool secondStep = checkCheckMate();
    //             gameBoard.set(startRow, startCol + 2 * x1, gameBoard.boxColor(startRow, startCol + 2 * x1));

    //             if (!firstStep && !secondStep) {
    //                 return true;
    //             }
    //         } else if (startRow == 1) {
    //             gameBoard.set(startRow, startCol + x1, 'K');
    //             bool firstStep = checkCheckMate();
    //             gameBoard.set(startRow, startCol + x1, gameBoard.boxColor(startRow, startCol + x1));
    //             gameBoard.set(startRow, startCol + 2 * x1, 'K');
    //             bool secondStep = checkCheckMate();
    //             gameBoard.set(startRow, startCol + 2 * x1, gameBoard.boxColor(startRow, startCol + 2 * x1));
    //             if (!firstStep && !secondStep) {
    //                 return true;
    //             }
    //         }
    //     }
    // }

    if (thisKing.isValid(startRow, startCol, endRow, endCol, endKind)) {
        return true;
    }

    return false;
}

bool Game::checkKnightMove(Piece startPiece, Piece endPiece) {

    int startRow = startPiece.getRow();
    char startCol = startPiece.getCol();
    int endRow = endPiece.getRow();
    char endCol = endPiece.getCol();

    Knight thisKnight = Knight(&startPiece);
    char endKind = endPiece.getKind();

    if (thisKnight.isValid(startRow, startCol, endRow, endCol, endKind)) {
        return true;
    }

    return false;
}

bool Game::checkEnPassant(int startRow, char startCol, int endRow, char endCol, char startKind) {
    if (startKind >= 65 && startKind <= 90) {
        // cap
        if (startRow == 4) {
            if (startRow == endRow + 1 && (endCol == startCol + 1 || endCol == startCol - 1)) {
                if (gameBoard.get(startRow, endCol).getKind() == 'p') {
                    if (recording.back().get(endRow + 1, endCol).getKind() == 'p') {
                        gameBoard.set(startRow, endCol, gameBoard.boxColor(startRow, endCol));
                        // gameBoard.move(startRow, startCol, endRow, endCol, 'P');
                        return true;
                    }
                }
            }
        }
    } else if (startKind >= 97 && startKind <= 122) {
        // lower
        if (startRow == 5) {
            if (startRow == endRow - 1 && (endCol == startCol + 1 || endCol == startCol - 1)) {
                if (gameBoard.get(startRow, endCol).getKind() == 'P') {
                    if (recording.back().get(endRow - 1, endCol).getKind() == 'P') {
                        gameBoard.set(startRow, endCol, gameBoard.boxColor(startRow, endCol));
                        // gameBoard.move(startRow, startCol, endRow, endCol, 'p');
                        return true;
                    }
                }
            }
        }
    }
    
    return false;
}

bool Game::checkPawnMove(Piece startPiece, Piece endPiece) {

    int startRow = startPiece.getRow();
    char startCol = startPiece.getCol();
    int endRow = endPiece.getRow();
    char endCol = endPiece.getCol();

    Pawn thisPawn = Pawn(&startPiece);
    char endKind = endPiece.getKind();

    char startKind = startPiece.getKind();

    if (checkEnPassant(startRow, startCol, endRow, endCol, startKind)) {
        return true;
    }

    if (thisPawn.isValid(startRow, startCol, endRow, endCol, endKind) ||
        checkEnPassant(startRow, startCol, endRow, endCol, startKind)) {
        if (endRow == 1 || endRow == 8) {
            char ki = 'k';

            // pawn cannot change to king
            while (ki == 'k' || ki == 'K') {
                cin >> ki;
            }
            
            gameBoard.set(startRow, startCol, ki);
        }

        if (startRow - endRow == -2 || startRow - endRow == 2) {
            // cout << "here 4" << endl;
            int rowIndex = startRow - (startRow - endRow) / 2;
            char midKind = gameBoard.get(rowIndex, startCol).getKind();

            if (midKind == ' ' || midKind == '-') {
                return true;
            }

            return false;
        }

        return true;
    }

    return false;
}

bool Game::checkQueenMove(Piece startPiece, Piece endPiece) {

    int startRow = startPiece.getRow();
    char startCol = startPiece.getCol();
    int endRow = endPiece.getRow();
    char endCol = endPiece.getCol();

    Queen thisQueen = Queen(&startPiece);
    char endKind = endPiece.getKind();

    int x = 0;
    int y = 0;

    if (thisQueen.isValid(startRow, startCol, endRow, endCol, endKind)) {

        if (endRow - startRow > 0) {
            y = 1;
        } else if (endRow - startRow < 0) {
            y = -1;
        }
        
        if (int(endCol) - int(startCol) > 0) {
            x = 1;
        } else if (int(endCol) - int(startCol) < 0) {
            x = -1;
        }
    } else {
        return false;
    }

    int ii = startRow + y;
    char jj = startCol + x;

    while (ii != endRow || jj != endCol) {
        char routeKind = gameBoard.get(ii, jj).getKind();

        if (!thisQueen.isValidMove(routeKind)) {
            return false;
        }

        ii += y;
        jj += x;
    }

    return true;
}

bool Game::checkRookMove(Piece startPiece, Piece endPiece) {

    int startRow = startPiece.getRow();
    char startCol = startPiece.getCol();
    int endRow = endPiece.getRow();
    char endCol = endPiece.getCol();

    Rook thisRook = Rook(&startPiece);
    char endKind = endPiece.getKind();

    int x = 0;
    int y = 0;

    if (thisRook.isValid(startRow, startCol, endRow, endCol, endKind)) {

        if (endRow - startRow > 0) {
            y = 1;
        } else if (endRow - startRow < 0) {
            y = -1;
        }
        
        if (int(endCol) - int(startCol) > 0) {
            x = 1;
        } else if (int(endCol) - int(startCol) < 0) {
            x = -1;
        }
    } else {
        return false;
    }

    int ii = startRow + y;
    char jj = startCol + x;

    while (ii != endRow || jj != endCol) {
        char routeKind = gameBoard.get(ii, jj).getKind();

        if (!thisRook.isValidMove(routeKind)) {
            return false;
        }

        ii += y;
        jj += x;
    }

    return true;
}

bool Game::checkTurn(char kind) {

    string color = "";
    if (kind >= 65 && kind <= 90) {
        color = "white";
    } else if (kind >= 97 && kind <= 122) {
        color = "black";
    }

    if (turn % 2 == 0) {
        if (color == "white") {
            return true;
        }
    } else {
        if (color == "black") {
            return true;
        }
    }

    cout << "Wrong turn" << endl;
    return false;
}

bool Game::checkMove(int startRow, char startCol, int endRow, char endCol) {

    if (startRow > 8 || 
        startRow < 1 ||
        startCol < 'a' ||
        startCol > 'h' ||
        endRow > 8 || 
        endRow < 1 ||
        endCol < 'a' ||
        endCol > 'h') {

        cout << "position off-board!" << endl;
        return false;
    }

    Piece startPiece = gameBoard.get(startRow, startCol);
    Piece endPiece = gameBoard.get(endRow, endCol);

    if (startPiece.getKind() == 'p' || startPiece.getKind() == 'P') {
        return checkPawnMove(startPiece, endPiece);
    } else if (startPiece.getKind() == 'q' || startPiece.getKind() == 'Q') {
        return checkQueenMove(startPiece, endPiece);
    } else if (startPiece.getKind() == 'r' || startPiece.getKind() == 'R') {
        return checkRookMove(startPiece, endPiece);
    } else if (startPiece.getKind() == 'n' || startPiece.getKind() == 'N') {
        return checkKnightMove(startPiece, endPiece);
    } else if (startPiece.getKind() == 'b' || startPiece.getKind() == 'B') {
        return checkBishopMove(startPiece, endPiece);
    } else if (startPiece.getKind() == 'k' || startPiece.getKind() == 'K') {
        return checkKingMove(startPiece, endPiece);
    }

    return false;
}

void Game::handleMove(string start, string finish) {

    int startRow = int(start.at(1)) - 48;
    char startCol = start.at(0);
    int endRow = int(finish.at(1)) - 48;
    char endCol = finish.at(0);

    move(9 - startRow, startCol, 9 - endRow, endCol);
}

void Game::move(int startRow, char startCol, int endRow, char endCol) {

    bool legal = checkMove(startRow, startCol, endRow, endCol);

    char startKind = gameBoard.get(startRow, startCol).getKind();
    char endKind = gameBoard.get(endRow, endCol).getKind();

    if (legal && checkTurn(startKind)) {
        if (turn == 0) {
            Board boardShot = Board(&gameBoard);
            recording.push_back(boardShot);
        }
        // when game is checkmate cannot play a move that does not solve the checkmate.
        if (isCheckMate) {
            gameBoard.move(startRow, startCol, endRow, endCol, startKind);
            isCheckMate = checkCheckMate();

            if (isCheckMate) {
                gameBoard.set(startRow, startCol, startKind);
                gameBoard.set(endRow, endCol, endKind);
            }
        } else {
            gameBoard.move(startRow, startCol, endRow, endCol, gameBoard.get(startRow, startCol).getKind());
            isCheckMate = checkCheckMate();
            turn++;
        }

        Board boardShot = Board(&gameBoard);
        recording.push_back(boardShot);
    } else {
        cout << "invalid move" << endl;
    }
}

bool Game::checkCheckMate() {
    bool inCheck = false;
    Piece blackKingPos = gameBoard.getKing('k');
    for (int ii = 1; ii <= 8; ++ii) {
        for (char jj = 'a'; jj <= 'h'; ++jj) {
            if (!(ii == blackKingPos.getRow() && jj == blackKingPos.getCol())) {
                int startRow = gameBoard.get(ii, jj).getRow();
                char startCol = gameBoard.get(ii, jj).getCol();
                int endRow = blackKingPos.getRow();
                char endCol = blackKingPos.getCol();

                bool isCheck = checkMove(startRow, startCol, endRow, endCol);
                if (isCheck) {
                    cout << "Black is in check." << endl;
                    inCheck = true;
                    break;
                }
            }
        }
    }

    Piece whiteKingPos = gameBoard.getKing('K');
    for (int ii = 1; ii <= 8; ++ii) {
        for (char jj = 'a'; jj <= 'h'; ++jj) {
            if (ii != whiteKingPos.getRow() && jj != whiteKingPos.getCol()) {
                int startRow = gameBoard.get(ii, jj).getRow();
                char startCol = gameBoard.get(ii, jj).getCol();
                int endRow = whiteKingPos.getRow();
                char endCol = whiteKingPos.getCol();
                
                bool isCheck = checkMove(startRow, startCol, endRow, endCol);

                if (isCheck) {
                    cout << "White is in check." << endl;
                    inCheck = true;
                    break;
                }
            }
        }
    }

    return inCheck;
}

bool Game::checkEat(int row, char col) {
    bool inCheck = false;
    Piece blackKingPos = gameBoard.get(row, col);
    for (int ii = 1; ii <= 8; ++ii) {
        for (char jj = 'a'; jj <= 'h'; ++jj) {
            if (!(ii == blackKingPos.getRow() && jj == blackKingPos.getCol())) {
                int startRow = gameBoard.get(ii, jj).getRow();
                char startCol = gameBoard.get(ii, jj).getCol();
                int endRow = blackKingPos.getRow();
                char endCol = blackKingPos.getCol();
                
                bool isCheck = checkMove(startRow, startCol, endRow, endCol);
                if (isCheck) {
                    inCheck = true;
                }
            }
        }
    }

    return inCheck;
}

void Game::setPlayer(int num, bool isMachine) {
    playerList[num].setBot(isMachine);
}

Player Game::getTurn() {
    if (turn % 2 == 1) {
        return playerList[1];
    } else {
        return playerList[0];
    }
}

Player Game::getPlayer(int index) {
    return playerList[index];
}

void Game::handleSetUpPlus(char pieceKind, string position) {
    int endRow = int(position.at(1)) - 48;
    char endCol = position.at(0);

    gameBoard.set(9 - endRow, endCol, pieceKind);
}

void Game::handleSetUpMinus(string position) {
    int endRow = int(position.at(1)) - 48;
    char endCol = position.at(0);

    gameBoard.set(9 - endRow, endCol, gameBoard.boxColor(9 - endRow, endCol));
}

void Game::handleSetUpEquals(string color) {
    if (color == "black") {
        turn = 1;
    } else if (color == "white") {
        turn = 0;
    }
}

bool Game::checkSetUp() {
    // check
    bool kingCheck = checkCheckMate();

    bool pawnCheck = false;
    bool multiKing = false;
    string kingNum = "";

    for (int ii = 1; ii <= 8; ++ii) {
        for (char jj = 'a'; jj <= 'h'; ++jj) {
            char kind = gameBoard.get(ii, jj).getKind();
            
            if (ii == 1 || ii == 8) {
                if (kind == 'p' && kind == 'P') {
                    pawnCheck = true;
                }
            }

            if (kind == 'k' || kind == 'K') {
                kingNum += kind;
            }
        }
    }

    if (kingNum.length() != 2) {
        multiKing = true;
    } else {
        if (kingNum != "Kk" && kingNum != "kK") {
            multiKing = true;
        }
    }

    bool res = true;

    if (multiKing || pawnCheck || kingCheck) {
        cout << "board is not valid" << endl;
        res = false;
    }

    if (multiKing) {
		cout << "the board should contain exactly one white king and exactly one black king" << endl;
    }

    if (pawnCheck) {
		cout << "the board should have no pawns on the first or last row of the board" << endl;
    }

    if (kingCheck) {
        cout << "the board should have no king in check" << endl;
    }

    return res;
}

void Game::moveAi(int level) {
    if (level == 1) {
        randomMove(getTurn().getId());
    }
}

void Game::randomMove(int id) {
    if (id == 0) {
        int randRow = rand() % 8 + 1;
        int randCol = rand() % 8;
        char randColchar = char(randCol + 97);

        if (gameBoard.get(randRow, randColchar).getKind() >= 65 && gameBoard.get(randRow, randColchar).getKind() <= 90) {
            
            while (true) {
                int endrandRow = rand() % 8 + 1;
                int endrandCol = rand() % 8;
                char endrandColchar = char(endrandCol + 97);

                if (checkMove(randRow, randColchar, endrandRow, endrandColchar)) {
                    gameBoard.move(randRow, randColchar, endrandRow, endrandColchar, gameBoard.get(randRow, randColchar).getKind());
                    isCheckMate = checkCheckMate();

                    gameBoard.printBoard();
                    
                    Board boardShot = Board(&gameBoard);
                    recording.push_back(boardShot);

                    turn++;
                    break;
                }
            }
        } else {
            randomMove(id);
        }
    } else {

    }
}

void Game::handleRegret() {
    cout << recording.size() << endl;
    for (int ii = 1; ii <= 8; ++ii) {
        for (char jj = 'a'; jj <= 'h'; ++jj) {
            char kind = recording[recording.size() - 3].get(ii, jj).getKind();
            gameBoard.set(ii, jj, kind);
        }
    }

    recording.pop_back();
    recording.pop_back();

    turn -= 2;
}
