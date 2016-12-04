#pragma once

#include "Map.hpp"
#include "Knowledge.hpp"
#include "Position.hpp"
#include <vector>
#include <SWI-cpp.h>

/*

(x,y) = position

Si Lumiere(x,y) => Portal(x,y)
Si Portal(x,y) => Sortir()

Si Odeur(x-1,y) & Odeur(x+1,y) & Odeur(x,y-1) & Odeur(x,y+1) => Monstre(x,y)
Si Vent(x-1,y) & Vent(x+1,y) & Vent(x,y-1) & Vent(x,y+1) => Crevasse(x,y)
Si Tirer(x,y) => !Monstre(x,y)
Si !Monstre(x,y) & !Crevasse(x,y) => Safe(x,y)
*/

class Player {
public:
    Player(Map& map);
    Position getPosition() { return m_position; }
    Map& getMap() { return m_map; };

    void updateEnvironment();
    void playRound();
    int getScore() {return score;};
private:
    // Attributes
    Position m_position;
    Map& m_map;
    unsigned int score;
    
    int getNextMovement();
};
