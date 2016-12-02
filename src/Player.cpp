#include "Player.hpp"
#include <iostream>
#include <string>

Player::Player(Map& map) : m_map(map) {
    m_position.x = 0;
    m_position.y = 0;
}

void Player::updateEnvironment() {
    const std::string pos_string = std::to_string(m_position.x) + "," + std::to_string(m_position.y);
    const char* pos = pos_string.c_str();
    std::cout << "p:" << pos << std::endl;
    PlTermv coord(pos);

    PlTermv k(1);
    //If we detect light
    if(m_map.getCase(m_position.x, m_position.y).portal) {
        std::cout << "Light at pos " << pos << std::endl;
        k[0] = PlCompound("light", coord);
        PlQuery q("assert", k);
        q.next_solution();
    }
    k[0] = PlCompound("visited", coord);
    PlQuery q("assert", k);
    q.next_solution();
    std::cout << "On pos " << pos << std::endl;

    /*Case u = m_map.getCase(m_position.x, m_position.y - 1);
    Case d = m_map.getCase(m_position.x, m_position.y + 1);
    Case l = m_map.getCase(m_position.x - 1, m_position.y);
    Case r = m_map.getCase(m_position.x + 1, m_position.y);
    m_knowledgeMap[m_position.y][m_position.x].odor = u.monster || d.monster || l.monster || r.monster;
    m_knowledgeMap[m_position.y][m_position.x].wind = u.hole || d.hole || l.hole || r.hole;
    m_knowledgeMap[m_position.y][m_position.x].up = u.walkable;
    m_knowledgeMap[m_position.y][m_position.x].down = d.walkable;
    m_knowledgeMap[m_position.y][m_position.x].left = l.walkable;
    m_knowledgeMap[m_position.y][m_position.x].right = r.walkable;*/
}

void Player::playRound() {
    updateEnvironment();
}
