#pragma once

#include "SWI-cpp.h"
#include "Player.hpp"
#include "Map.hpp"

Map GLOBALMAP;

PREDICATE(light, 2)
{
    unsigned int x = int(A1);
    unsigned int y = int(A2);
    return Player::instance(GLOBALMAP)->isLight(x, y);
}

PREDICATE(next_movement, 0) {
    /*PlTermv arg(2);
    arg[0] = 0; //get player current x
    arg[1] = 0; //get player current y
    if(PlCall("runOut", arg)) {
        std::cout << "Portail trouvé, on sort" << std::endl;
        return RUNOUT;
    }
    std::cout << "Portail non trouvé, on ne bouge pas" << std::endl;
    return DONOTHING;*/
    return true;
}
