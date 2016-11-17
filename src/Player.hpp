#pragma once

#include "Map.hpp"
#include "Knowledge.hpp"

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
