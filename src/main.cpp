#include <iostream>
#include <exception>

// #include "Data.h"
// #include "Logic.h"
#include "Displayer.h"

int main(int argc, char* argv[]) {
    // Initialise data
    /*Data data();*/

    // Initialize graphic interface
    Displayer displayer;
    std::thread displayerThread;

    try {
        // Launch graphic interface
        displayerThread = displayer.start();
        displayer.waitReady();

        // Do stuff with data
        /*Logic logic(data);*/
        /*Logic.start();*/
        throw std::logic_error("Nothing to do !");

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
