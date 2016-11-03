#include <iostream>
#include <algorithm>
#include "Displayer.h"

/* Constructors */
Displayer::Displayer(int width, int height): m_width(width), m_height(height) {}

/* Methods */
std::thread Displayer::start() {
    m_ready.lock();
    return std::thread(&Displayer::run, this);
}

void Displayer::waitReady() {
    m_ready.lock();
}

void Displayer::run() {
    // Open window
    m_pWindow = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(m_width, m_height),
            "Application");
    m_pWindow->setVerticalSyncEnabled(true);
    m_pWindow->setFramerateLimit(60);
    m_ready.unlock();

    // Main loop while window is open
    while(m_pWindow->isOpen()) {
        handleEvents();
        drawScene();
    }
}

void Displayer::handleEvents() {
    if(m_pWindow) {
        sf::Event event;
        while(m_pWindow->pollEvent(event)) {
            handleEvent(event);
        }
    }
}

// Default
void Displayer::handleEvent(sf::Event& event) {
    switch(event.type) {
    case sf::Event::Closed:
        m_pWindow->close();
    default:
        break;
    }
}

// Default
void Displayer::drawScene() {
    m_pWindow->clear(sf::Color(0, 0, 0));
    m_pWindow->display();
}
