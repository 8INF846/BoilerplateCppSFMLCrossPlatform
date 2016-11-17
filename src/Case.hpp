#pragma once

struct Case {
public:
    // Attributes
    bool monster;
    bool crevasse;
    bool portal;
    bool walkable;

    // Constructors
    Case(bool walkable)
            : monster(false)
            , crevasse(false)
            , portal(false)
            , walkable(walkable) {}
    Case(bool monster, bool crevasse, bool portal)
            : monster(monster)
            , crevasse(crevasse)
            , portal(portal)
            , walkable(true) {}
};
