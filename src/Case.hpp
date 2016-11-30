#pragma once

struct Case {
public:
    // Attributes
    bool monster;
    bool hole;
    bool portal;
    bool walkable;
    bool visited;

    // Constructors
    Case()  : monster(false)
            , hole(false)
            , portal(false)
            , walkable(true) {}
    Case(bool walkable)
            : monster(false)
            , hole(false)
            , portal(false)
            , walkable(walkable) {}
    Case(bool monster, bool hole, bool portal)
            : monster(monster)
            , hole(hole)
            , portal(portal)
            , walkable(true) {}
};
