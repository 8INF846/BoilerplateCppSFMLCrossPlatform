#include "Player.hpp"
#include "SWI-cpp.h"
#include <iostream>

Player *Player::s_instance = nullptr;

Player::Player(Map& map) : m_map(map) {
    m_position.x = 0;
    m_position.y = 0;
    initKnowledgeMap();
}

void Player::initKnowledgeMap() {
    m_knowledgeMap.clear();
    for(size_t l = 0; l < this->m_map.size(); ++l) {
        std::vector<Knowledge> line;
        for(size_t c = 0; c < this->m_map.size(); ++c) {
            Knowledge k;
            k.odor = false;
            k.wind = false;
            k.light = false;
            k.up = false;
            k.down = false;
            k.left = false;
            k.right = false;
            k.visited = false;
            line.push_back(k);
        }
        m_knowledgeMap.push_back(line);
    }
}

void Player::updateEnvironment() {
    Case u = m_map.getCase(m_position.x, m_position.y - 1);
    Case d = m_map.getCase(m_position.x, m_position.y + 1);
    Case l = m_map.getCase(m_position.x - 1, m_position.y);
    Case r = m_map.getCase(m_position.x + 1, m_position.y);
    m_knowledgeMap[m_position.y][m_position.x].odor = u.monster || d.monster || l.monster || r.monster;
    m_knowledgeMap[m_position.y][m_position.x].wind = u.hole || d.hole || l.hole || r.hole;
    m_knowledgeMap[m_position.y][m_position.x].light = m_map.getCase(m_position.x, m_position.y).portal;
    m_knowledgeMap[m_position.y][m_position.x].up = u.walkable;
    m_knowledgeMap[m_position.y][m_position.x].down = d.walkable;
    m_knowledgeMap[m_position.y][m_position.x].left = l.walkable;
    m_knowledgeMap[m_position.y][m_position.x].right = r.walkable;
    m_knowledgeMap[m_position.y][m_position.x].visited = true;
}

bool Player::isOdor(unsigned int x, unsigned int y) {
    if(x > m_knowledgeMap.size() || y > m_knowledgeMap.size()) return false;
    return m_knowledgeMap[y][x].odor;
}

bool Player::isWind(unsigned int x, unsigned int y) {
    if(x > m_knowledgeMap.size() || y > m_knowledgeMap.size()) return false;
    return m_knowledgeMap[y][x].wind;
}

bool Player::isLight(unsigned int x, unsigned int y) {
    if(x > m_knowledgeMap.size() || y > m_knowledgeMap.size()) return false;
    return m_knowledgeMap[y][x].light;
}

bool Player::isUp(unsigned int x, unsigned int y) {
    if(x > m_knowledgeMap.size() || y > m_knowledgeMap.size()) return false;
    return m_knowledgeMap[y][x].up;
}

bool Player::isDown(unsigned int x, unsigned int y) {
    if(x > m_knowledgeMap.size() || y > m_knowledgeMap.size()) return false;
    return m_knowledgeMap[y][x].down;
}

bool Player::isLeft(unsigned int x, unsigned int y) {
    if(x > m_knowledgeMap.size() || y > m_knowledgeMap.size()) return false;
    return m_knowledgeMap[y][x].left;
}

bool Player::isRight(unsigned int x, unsigned int y) {
    if(x > m_knowledgeMap.size() || y > m_knowledgeMap.size()) return false;
    return m_knowledgeMap[y][x].right;
}

void Player::playRound() {
    updateEnvironment();
    std::cout << "play round" << std::endl;
}
