#include <iostream>
#include <exception>

// #include "Data.h"
// #include "Logic.h"
#include "SWI-cpp.h"
#include "Displayer.h"
#include "Player.hpp"

int main(int argc, char* argv[]) {
    PlEngine e(argv[0]);

    // Initialize graphic interface
    Map map;
    Player player(map);
    Displayer displayer(map, player);
    std::thread displayerThread;

    try {
        // Launch graphic interface
        displayerThread = displayer.start();
        displayer.waitReady();

        std::cout << "Wait Spacebar" << std::endl;
        while(displayer.isOpen()) {
            if(displayer.updatePlayer()) {
                std::cout << "Update Player" << std::endl;
                player.playRound();
                std::cout << "Wait Spacebar" << std::endl;
                displayer.waitUpdate();
                if(player.hasWin()) {
                    map.initNextRound();
                    player.initNextRound();
                }
            }
        }
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
