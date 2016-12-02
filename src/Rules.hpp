#pragma once

#include "SWI-cpp.h"
#include "Knowledge.hpp"

PREDICATE(next_movement, 2) {
    PlTermv coord(2);
    coord[0] = PlTerm((long)A1);
    coord[1] = PlTerm((long)A2);

    try {
        if(PlCall("runOut", coord)) {
            std::cout << "Portail trouvé, on sort" << std::endl;
            return RUNOUT;
        }
    } catch (PlException &ex) {

    }
    std::cout << "Portail non trouvé, on ne bouge pas" << std::endl;
    return DONOTHING;
}
