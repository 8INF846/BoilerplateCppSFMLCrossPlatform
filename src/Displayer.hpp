#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <memory>
#include <thread>
#include <mutex>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "Player.hpp"

class Displayer {
public:
    /* Constructor */
    Displayer(Map& map, Player& p, int width = 854, int height = 480);

    /* methods */
    // Start displaying sudoku while it is being solved.
    std::thread start();

    // Wait thread until displayer is ready to display data.
    void waitReady();

    bool updatePlayer() {
        if(m_updateReady) std::cout << "Update player" << std::endl;
        return m_updateReady;
    }
    void waitUpdate() { m_updateReady = false; }
    bool isOpen() { return m_isOpen; }

private:
    /* Attributes */
    // Whether or not window is ready
    std::mutex m_ready;

    /* Methods */
    // Display loop
    void run();
    // Events loop
    void handleEvents();

    // Object to render
    Map& map;
    Player& player;

protected:
    /* Attributes */
    // Width of the window
    int m_width;
    // Height of the window
    int m_height;
    // Pointer to the window
    std::unique_ptr<sf::RenderWindow> m_pWindow;

    /* Methods */
    // Display scene into window.
    virtual void drawScene();

    // Handle client input.
    virtual void handleEvent(sf::Event& event);

    bool m_updateReady;
    bool m_isOpen;
};

#endif
