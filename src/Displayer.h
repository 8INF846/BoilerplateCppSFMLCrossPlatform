#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <memory>
#include <thread>
#include <mutex>

#include <SFML/Graphics.hpp>

class Displayer {
public:
    /* Constructor */
    Displayer(int width = 854, int height = 480);

    /* methods */
    // Start displaying sudoku while it is being solved.
    std::thread start();

    // Wait thread until displayer is ready to display data.
    void waitReady();

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

private:
    /* Attributes */
    // Whether or not window is ready
    std::mutex m_ready;

    /* Methods */
    // Display loop
    void run();
    // Events loop
    void handleEvents();
};

#endif
