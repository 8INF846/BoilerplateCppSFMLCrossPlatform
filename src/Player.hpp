#pragma once

#include "Map.hpp"
#include "Knowledge.hpp"
#include "Position.hpp"

#include <vector>

/*

(x,y) = position

Si Lumiere(x,y) => Portal(x,y)
Si Portal(x,y) => Sortir()

Si Odeur(x-1,y) & Odeur(x+1,y) & Odeur(x,y-1) & Odeur(x,y+1) => Monstre(x,y)
Si Vent(x-1,y) & Vent(x+1,y) & Vent(x,y-1) & Vent(x,y+1) => Crevasse(x,y)
Si Tirer(x,y) => !Monstre(x,y)
Si !Monstre(x,y) & !Crevasse(x,y) => Safe(x,y)

enum Action {
    ShootUp,
    ShootDown,
    ShootLeft,
    ShootRight,
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight
};
*/

class Player {
public:
    static Player *instance(Map& map)
    {
        if (s_instance == nullptr)
          s_instance = new Player(map);
        return s_instance;
    }

    Position getPosition() { return m_position; }
    Map& getMap() { return m_map; };
    std::vector<std::vector<Knowledge>>& getKnowledgeMap() { return m_knowledgeMap; }

    void initKnowledgeMap();
    void updateEnvironment();

    bool isOdor(unsigned int x, unsigned int y);
    bool isWind(unsigned int x, unsigned int y);
    bool isLight(unsigned int x, unsigned int y);
    bool isUp(unsigned int x, unsigned int y);
    bool isDown(unsigned int x, unsigned int y);
    bool isLeft(unsigned int x, unsigned int y);
    bool isRight(unsigned int x, unsigned int y);

    void playRound();
private:
    static Player *s_instance;
    Player(Map& map);
    // Attributes
    Position m_position;
    Map& m_map;
    std::vector<std::vector<Knowledge>> m_knowledgeMap;
};
