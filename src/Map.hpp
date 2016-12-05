#pragma once

#include "Case.hpp"
#include <stdlib.h>
#include <vector>

class Map {
public:
    Map(const size_t baseSize = 3);

    void initializeMap();
    void initNextRound();

    size_t size() { return mapSize; }

    const Case getCase(const unsigned int col, const unsigned int row);
    bool hasWind(const unsigned int col, const unsigned int row);
    bool hasPoop(const unsigned int col, const unsigned int row);
    void shoot(const unsigned int col, const unsigned int row);

    Case operator()(const unsigned int col, const unsigned int row) {
        return this->getCase(col, row);
    }

private:
    std::vector<std::vector<Case>> cases;
    size_t mapSize;
};
