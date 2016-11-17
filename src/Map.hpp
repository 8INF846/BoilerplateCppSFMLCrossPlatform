#pragma once

class Map {
public:
    Case operator()(int i, int j) {
        if(i < 0 || cases.size() <= i) {
            return Case(false);
        }
        if(j < 0 || cases[i].size() <= j) {
            return Case(false);
        }
        return cases[i][j];

private:
    std::vector<std::vector<Case>> cases;
};
