#include "Map.hpp"

#include <iostream>
#include <random>

#define MONSTER_PROB  20
#define HOLE_PROB     10

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
    unsigned int portalR = portal_pos_rand(e1);
    unsigned int portalC = portal_pos_rand(e1);
    this->cases[portalR][portalC] = Case(false, false, true);
    //2. Init the others
    for(size_t r = 0; r < this->mapSize; ++r) {
        for(size_t c = 0; c < this->mapSize; ++c) {
            if(c == 0 && r == 0) {
                this->cases[r][c] = Case(false, false, (portalC == c) && (portalR == r));
            } else if (c != portalC && r != portalR) {
                bool isMonster = percent_rand(e1) < MONSTER_PROB;
                bool isHole = percent_rand(e1) < HOLE_PROB;
                this->cases[r][c] = Case(isMonster, isHole, false);
            }
        }
    }
}

void Map::initNextRound() {
    ++this->mapSize;
    this->initializeMap();
}
