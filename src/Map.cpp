#include "Map.hpp"

#include <iostream>
#include <random>
#include "SWI-cpp.h"

#define MONSTER_PROB  10
#define HOLE_PROB     5

Map::Map(const size_t baseSize) : mapSize(baseSize) {
    initializeMap();
}

void Map::initializeMap() {
    this->cases = std::vector<std::vector<Case>>(mapSize, std::vector<Case>(this->mapSize));
    //1. Init portal
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> portal_pos_rand(0, this->mapSize-1);
    std::uniform_int_distribution<int> percent_rand(0, 100);
    unsigned int portalR = 0; unsigned int portalC = 0;
    while(portalR == 0 || portalC == 0) {
        portalR = portal_pos_rand(e1);
        portalC = portal_pos_rand(e1);
    }
    this->cases[portalR][portalC] = Case(false, false, true);
    //2. Init the others
    for(size_t r = 0; r < this->mapSize; ++r) {
        for(size_t c = 0; c < this->mapSize; ++c) {
            if(c == 0 && r == 0) {
                this->cases[r][c] = Case(false, false, (portalC == c) && (portalR == r));
            } else if (c != portalC || r != portalR) {
                bool isMonster = percent_rand(e1) < MONSTER_PROB;
                bool isHole = percent_rand(e1) < HOLE_PROB; //TODO : (c==1&&r==1);//(c==0&&r==2) || (c==2&&r==0);//
                if(isMonster) isHole = false;
                this->cases[r][c] = Case(isMonster, isHole, false);
            }
        }
    }
}

const Case Map::getCase(const unsigned int col, const unsigned int row) {
    if(row >= mapSize || col >= mapSize) {
        return Case(false);
    }
    return this->cases[row][col];
}

void Map::initNextRound() {
    ++this->mapSize;
    this->initializeMap();
    //remove predicate from prolog database
    for(size_t r = 0; r < this->mapSize; ++r) {
        for(size_t c = 0; c < this->mapSize; ++c) {
            PlTermv arg(2);
            arg[0] = (long)c;
            arg[1] = (long)r;
            PlCall("removeLight", arg);
            PlCall("removePoop", arg);
            PlCall("removeWind", arg);
            PlCall("removeWalkable", arg);
            PlCall("removeVisited", arg);
            PlCall("removeShooted", arg);
            PlCall("removeHole", arg);
        }
    }
}

bool Map::hasWind(const unsigned int col, const unsigned int row) {
    Case u = this->getCase(col, row - 1);
    Case d = this->getCase(col, row + 1);
    Case l = this->getCase(col - 1, row);
    Case r = this->getCase(col + 1, row);
    return u.hole || d.hole || l.hole || r.hole;
}

bool Map::hasPoop(const unsigned int col, const unsigned int row) {
    Case u = this->getCase(col, row - 1);
    Case d = this->getCase(col, row + 1);
    Case l = this->getCase(col - 1, row);
    Case r = this->getCase(col + 1, row);
    return u.monster || d.monster || l.monster || r.monster;
}

void Map::shoot(const unsigned int col, const unsigned int row) {
    PlTermv currentPos(2);
    currentPos[0] = (long)col;
    currentPos[1] = (long)row;
    PlCall("setShooted", currentPos);

    if(row >= mapSize || col >= mapSize || !this->cases[row][col].monster) {
        return;
    }
    
    this->cases[row][col].monster = false;
    //Remove poop if we need
    if(!this->hasPoop(col-1, row)) {
        PlTermv coord(2);
        coord[0] = (long)col-1;
        coord[1] = (long)row;
        PlCall("removePoop", coord);
    }
    if(!this->hasPoop(col+1, row)) {
        PlTermv coord(2);
        coord[0] = (long)col+1;
        coord[1] = (long)row;
        PlCall("removePoop", coord);
    }
    if(!this->hasPoop(col, row-1)) {
        PlTermv coord(2);
        coord[0] = (long)col;
        coord[1] = (long)row-1;
        PlCall("removePoop", coord);
    }
    if(!this->hasPoop(col, row+1)) {
        PlTermv coord(2);
        coord[0] = (long)col;
        coord[1] = (long)row+1;
        PlCall("removePoop", coord);
    }
}
