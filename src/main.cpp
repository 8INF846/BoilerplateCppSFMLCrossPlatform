#include <iostream>
#include <exception>

#include "SWI-cpp.h"
#include "Displayer.hpp"
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
                player.playRound();
                std::cout << "Wait Spacebar" << std::endl;
                displayer.waitUpdate();
                if(player.hasWin()) {
                    std::cout << "#################################" << std::endl
                              << "#           PLAYER WINS         #" << std::endl
                              << "#################################" << std::endl
                              << "[        INIT NEXT LEVEL        ]" << std::endl;
                    map.initNextRound();
                    player.initNextRound();
                }
            }
        }

        // Wait for graphic interface to be closed before exiting
        displayerThread.join();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;

        // Wait for graphic interface to be closed before exiting
        displayerThread.join();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
