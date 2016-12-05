#include "Displayer.hpp"
#include "Player.hpp"
#include "SWI-cpp.h"
#include <iostream>
#include <algorithm>

/* Constructors */
Displayer::Displayer(Map &map, Player& p, int width, int height): map(map),
player(p), m_width(width), m_height(height), m_updateReady(false), m_isOpen(true)
{}

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
    "TP3 IA, the endless forest.");
    m_pWindow->setKeyRepeatEnabled(false);
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
        m_isOpen = false;
        break;
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Space) {
            m_updateReady = true;
        }
    default:
        break;
    }
}

// Default
void Displayer::drawScene() {
    //Load texture
    sf::Texture textureWalkable1;
    textureWalkable1.loadFromFile("img/walkable1.png", sf::IntRect(0, 0, 100, 100));
    sf::Texture textureWalkable2;
    textureWalkable2.loadFromFile("img/walkable2.png", sf::IntRect(0, 0, 100, 100));
    sf::Texture textureMonster;
    textureMonster.loadFromFile("img/monster.png", sf::IntRect(0, 0, 100, 100));
    sf::Texture textureMonsterDown;
    textureMonsterDown.loadFromFile("img/monster_down.png", sf::IntRect(0, 0, 100, 100));
    sf::Texture textureHole;
    textureHole.loadFromFile("img/hole.png", sf::IntRect(0, 0, 100, 100));
    sf::Texture texturePortal;
    texturePortal.loadFromFile("img/portal.png", sf::IntRect(0, 0, 100, 100));
    sf::Texture texturePoop;
    texturePoop.loadFromFile("img/poop.png", sf::IntRect(0, 0, 100, 100));
    sf::Texture textureWind;
    textureWind.loadFromFile("img/wind.png", sf::IntRect(0, 0, 100, 100));
    sf::Texture texturePlayer;
    texturePlayer.loadFromFile("img/player.png", sf::IntRect(0, 0, 100, 100));

    //Scale size
    unsigned int size = this->m_pWindow->getSize().x / this->map.size();
    float scaling = (float)size/100.;

    //Draw scene
    m_pWindow->clear(sf::Color(0, 0, 0));
    for(size_t r = 0; r < this->map.size(); ++r) {
        for(size_t c = 0; c < this->map.size(); ++c) {
            sf::Sprite sprite;
            Case caseToRender = this->map.getCase(c, r);
            if(caseToRender.portal) {
                sprite.setTexture(texturePortal, true);
            } else if(caseToRender.hole) {
                sprite.setTexture(textureHole, true);
            } else if(caseToRender.monster) {
                sprite.setTexture(textureMonster, true);
            } else if (caseToRender.walkable) {
                sprite.setTexture(((r+c) % 2 == 0) ? textureWalkable1 : textureWalkable2, true);
            }

            sprite.setPosition(size*c, size*r);
            sprite.setScale(scaling, scaling);
            m_pWindow->draw(sprite);

            if(this->map.hasPoop(c, r)) {
                sf::Sprite spritePoop;
                spritePoop.setPosition(size*c, size*r);
                spritePoop.setTexture(texturePoop, true);
                spritePoop.setScale(scaling, scaling);
                m_pWindow->draw(spritePoop);
            }
            if(this->map.hasWind(c, r)) {
                sf::Sprite spriteWind;
                spriteWind.setPosition(size*c, size*r);
                spriteWind.setTexture(textureWind, true);
                spriteWind.setScale(scaling, scaling);
                m_pWindow->draw(spriteWind);
            }

            Position posPlayer = this->player.getPosition();
            if(c == posPlayer.x && r == posPlayer.y) {
                sf::Sprite spritePlayer;
                spritePlayer.setPosition(size*c, size*r);
                spritePlayer.setTexture(texturePlayer, true);
                spritePlayer.setScale(scaling, scaling);
                m_pWindow->draw(spritePlayer);
            }
        }
    }
    m_pWindow->display();
}
