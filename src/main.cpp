#include <iostream>
#include <exception>

// #include "Data.h"
// #include "Logic.h"
#include "Displayer.h"
#include "Map.hpp"
#include "SWI-cpp.h"
#include "Player.hpp"

Map GLOBALMAP;

PREDICATE(light, 2)
{
    unsigned int x = int(A1);
    unsigned int y = int(A2);
    return Player::instance(GLOBALMAP)->isLight(x, y);
}

PREDICATE(next_movement, 0) {
    PlTermv arg(2);
    arg[0] = 0; //get player current x
    arg[1] = 0; //get player current y
    if(PlCall("runOut", arg)) {
        std::cout << "Portail trouvé, on sort" << std::endl;
        return RUNOUT;
    }
    std::cout << "Portail non trouvé, on ne bouge pas" << std::endl;
    return DONOTHING;
}


int main(int argc, char* argv[]) {
    PlEngine e(argv[0]);
    PlTermv av(0);
    PlCall("next_movement", av);
    Player::instance(GLOBALMAP)->getKnowledgeMap()[0][0].light = true;
    PlCall("next_movement", av);

    // Initialize graphic interface
    for(int i = 0; i < 3; ++i)
    GLOBALMAP.initNextRound();
    Displayer displayer(GLOBALMAP);
    std::thread displayerThread;

    try {
        // Launch graphic interface
        displayerThread = displayer.start();
        displayer.waitReady();

        // Do stuff with data
        /*Logic logic(data);*/
        /*Logic.start();*/

        // Wait for graphic interface to be closed before exiting
        displayerThread.join();
    }
    catch(const std::exception& e) {
        // Do stuff before exiting
        /*Logic.clean()*/
        /*displayer.showError()*/
        std::cerr << e.what() << std::endl;

        // Wait for graphic interface to be closed before exiting
        displayerThread.join();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
