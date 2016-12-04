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

    const Case getCase(const unsigned int row, const unsigned int col);
    bool hasWind(const unsigned int row, const unsigned int col);
    bool hasPoop(const unsigned int row, const unsigned int col);
    void shoot(const unsigned int row, const unsigned int col);

    Case operator()(const unsigned int row, const unsigned  int col) {
        return getCase(row, col);
    }

private:
    std::vector<std::vector<Case>> cases;
    size_t mapSize;
};
