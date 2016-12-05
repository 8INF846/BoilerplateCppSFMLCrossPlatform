#pragma once

#include "Map.hpp"
#include "Knowledge.hpp"
#include "Position.hpp"
#include <vector>
#include <SWI-cpp.h>

class Player {
public:
    Player(Map& map);
    Position getPosition() { return m_position; }
    Map& getMap() { return m_map; };

    void updateEnvironment();
    void playRound();
    int getScore() {return score;};
    void initNextRound();
    bool hasWin() { return b_hasWin; }
private:
    // Attributes
    Position m_position;
    Map& m_map;
    unsigned int score;
    bool b_hasWin;

    int getNextMovement();
};
