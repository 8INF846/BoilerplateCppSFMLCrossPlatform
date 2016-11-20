#pragma once

#include "Case.hpp"
#include <stdlib.h>
#include <vector>

class Map {
public:
    Map(const size_t baseSize = 3);

    void initializeMap();
    void initNextRound();

    /*
    Case operator()(int i, int j) {
        if(i < 0 || cases.size() <= i) {
            return Case(false);
        }
        if(j < 0 || cases[i].size() <= j) {
            return Case(false);
        }
        return cases[i][j];
    }*/

private:
    std::vector<std::vector<Case>> cases;
    size_t mapSize;
};
