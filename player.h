#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Player {
  private:
    int id;
    string color;
  public:
    bool isBot;
    
    void setId(int num);
    void setColor(string str);
    void setBot(bool isMachine);

    int getId();
};

#endif