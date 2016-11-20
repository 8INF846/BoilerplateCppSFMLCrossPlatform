#include <iostream>
#include <exception>

// #include "Data.h"
// #include "Logic.h"
#include "Displayer.h"
#include "Map.hpp"

int main(int argc, char* argv[]) {
    // Initialise data
    /*Data data();*/

    // Initialize graphic interface
    Map map;
    for(int i = 0; i < 3; ++i)
    map.initNextRound();
    Displayer displayer(map);
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
