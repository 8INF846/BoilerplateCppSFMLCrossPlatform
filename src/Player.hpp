#pragma once

#include "Map.hpp"
#include "Knowledge.hpp"

/*

(x,y) = position

Si Lumiere(x,y) => Portal(x,y)
Si Portal(x,y) => Sortir()

Si Odeur(x-1,y) & Odeur(x+1,y) & Odeur(x,y-1) & Odeur(x,y+1) => Monstre(x,y)
Si Vent(x-1,y) & Vent(x+1,y) & Vent(x,y-1) & Vent(x,y+1) => Crevasse(x,y)
Si Tirer(x,y) => !Monstre(x,y)
Si !Monstre(x,y) & !Crevasse(x,y) => Safe(x,y)
*/

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

class Player {
public:
    // Constructor
    Player(Position position, Map& map);

    // Methods
    void Play() {
        Knowledge knowledge = inspectEnvironment();
        Action action = chooseAction(knoledge);
        return action;
    }
private:
    // Attributes
    Position position;
    Map& map;
    Action action;

    // Methods
    Knowledge inspectEnvironment() {
        Case u = Map(position.x, position.y - 1);
        Case d = Map(position.x, position.y + 1);
        Case l = Map(position.x - 1, position.y);
        Case r = Map(position.x + 1, position.y);

        return Sensor(
            u.monster || d.monster || l.monster || r.monster,
            u.crevasse || d.crevasse || l.crevasse || r.crevasse,
            Map(position.x, position.y).portal,
            u.walkable,
            d.walkable,
            l.walkable,
            r.walkable);
    }
    Action chooseAction(const Knoledge& knoledge);
};
