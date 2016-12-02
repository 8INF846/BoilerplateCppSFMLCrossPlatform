#pragma once

#include "SWI-cpp.h"
#include "Knowledge.hpp"

PREDICATE(next_movement, 1) {

    try {
        if(PlCall("runOut", A1)) {
            std::cout << "Portail trouvé, on sort" << std::endl;
            return RUNOUT;
        }
    } catch (PlException &ex) {
        
    }
    std::cout << "Portail non trouvé, on ne bouge pas" << std::endl;
    return DONOTHING;
}
