#include <iostream>
#include <vector>

#include "game.h"
#include "board.h"
#include "pawn.h"
#include "piece.h"
#include "player.h"

using namespace std;

int main() {
    Game * g = new Game();
    g->newGame();

    int whiteScore = 0;
    int blackScore = 0;

    string cmd;

    while (!g->isOver) {
        cin >> cmd;
        if (cmd == "setup") {
            g->isSetUp = true;
            g->printGame();

            while (g->isSetUp) {
                cin >> cmd;
                if (cmd == "+") {
                    char pieceKind;
                    string position;
                    cin >> pieceKind >> position;

                    g->handleSetUpPlus(pieceKind, position);
                    g->printGame();
		    	} else if (cmd == "-") {
                    string position;
                    cin >> position;

                    g->handleSetUpMinus(position);
                    g->printGame();
		    	} else if(cmd == "=") {
                    string color;
                    cin >> color;

                    g->handleSetUpEquals(color);
                    g->printGame();
		    	} else if (cmd == "done") {
                    cout << "fuck" << endl;
                    cout << "setup" << g->checkSetUp() << endl;
                    cout << "isSetUp" << g->isSetUp << endl;
                    bool set = g->checkSetUp();
                    if (set) {
                        g->isSetUp = false;
                    }
		    	} 
            }
        }         
        if (cmd == "game") {
            string white_player;
            string black_player;

            cin >> white_player >> black_player;

            if (white_player == "computer1") {
                g->setPlayer(0, true);
            }

            if (black_player == "computer1") {
                g->setPlayer(1, true);
            }

            g->printGame();

            while (!cin.eof()) {
                if (g->getTurn().isBot) {
                    g->moveAi(1);
                    
                    continue;
                }

                cin >> cmd;
                if (cmd == "move") {
                    string start;
                    string finish;
                    string toWhat;

                    cin >> start >> finish;

                    g->handleMove(start, finish);
                    g->printGame();
                } 

                if (cmd == "resign") {
                    if (!g->getTurn().getId()) {
                        cout << "Black wins!" << endl;
                        blackScore += 1;
                    }

                    if (g->getTurn().getId()) {
                        cout << "White wins!" << endl;
                        whiteScore += 1;
                    }

                    g->newGame();
                    g->printGame();
                }

                if (cmd == "regret") {
                    g->handleRegret();
                    g->printGame();
                }
            }
            
            g->isOver = true;
        } 
    }

    cout << "Final Score:" << endl;
    cout << "White: " << whiteScore << endl;
    cout << "Black: " << blackScore - 1 << endl;

    return 0;
}