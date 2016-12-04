#include "Player.hpp"
#include <iostream>
#include <string>
#include "Rules.hpp"

Player::Player(Map& map) : m_map(map) {
    m_position.x = 0;
    m_position.y = 0;
}

void Player::updateEnvironment() {
    PlTermv coord(2);
    coord[0] = PlTerm((long)m_position.x);
    coord[1] = PlTerm((long)m_position.y);
    const std::string pos_string = std::to_string(m_position.x) + "," + std::to_string(m_position.y);
    const char* pos = pos_string.c_str();

    PlTermv k(1);
    //If we detect light
    if(m_map.getCase(m_position.x, m_position.y).portal) {
        std::cout << "Light at pos " << pos << std::endl;
        k[0] = PlCompound("light", coord);
        PlQuery q("assert", k);
        q.next_solution();
    }
    if(m_map.hasWind(m_position.x, m_position.y)) {
        std::cout << "Wind at pos " << pos << std::endl;
        k[0] = PlCompound("wind", coord);
        PlQuery q("assert", k);
        q.next_solution();
    }
    if(m_map.hasPoop(m_position.x, m_position.y)) {
        std::cout << "Poop at pos " << pos << std::endl;
        k[0] = PlCompound("poop", coord);
        PlQuery q("assert", k);
        q.next_solution();
    }
    if(m_map.getCase(m_position.x, m_position.y - 1).walkable) {
        PlTermv argWalk(2);
        argWalk[0] = PlTerm((long)m_position.x);
        argWalk[1] = PlTerm((long)(m_position.y-1));
        k[0] = PlCompound("walkable", argWalk);
        PlQuery q("assert", k);
        q.next_solution();
    }
    if(m_map.getCase(m_position.x, m_position.y + 1).walkable) {
        PlTermv argWalk(2);
        argWalk[0] = PlTerm((long)m_position.x);
        argWalk[1] = PlTerm((long)(m_position.y+1));
        k[0] = PlCompound("walkable", argWalk);
        PlQuery q("assert", k);
        q.next_solution();
    }
    if(m_map.getCase(m_position.x - 1, m_position.y).walkable) {
        PlTermv argWalk(2);
        argWalk[0] = PlTerm((long)(m_position.x-1));
        argWalk[1] = PlTerm((long)m_position.y);
        k[0] = PlCompound("walkable", argWalk);
        PlQuery q("assert", k);
        q.next_solution();
    }
    if(m_map.getCase(m_position.x + 1, m_position.y).walkable) {
        PlTermv argWalk(2);
        argWalk[0] = PlTerm((long)(m_position.x+1));
        argWalk[1] = PlTerm((long)m_position.y);
        k[0] = PlCompound("walkable", argWalk);
        PlQuery q("assert", k);
        q.next_solution();
    }
    k[0] = PlCompound("visited", coord);
    PlQuery q("assert", k);
    q.next_solution();
}

int Player::getNextMovement() {
    PlTermv coord(2);
    coord[0] = PlTerm((long)m_position.x);
    coord[1] = PlTerm((long)m_position.y);
    PlTermv coordsouth(2);
    coordsouth[0] = PlTerm((long)m_position.x);
    coordsouth[1] = PlTerm((long)(m_position.y+1));
    PlTermv coordNorth(2);
    coordNorth[0] = PlTerm((long)m_position.x);
    coordNorth[1] = PlTerm((long)m_position.y-1);

    if(PlCall("runOut", coord)) {
        return RUNOUT;
    }

    if(PlCall("safe", coord)) {
        std::cout << "SAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFE" << std::endl;
    }
    if(PlCall("walkable", coordsouth)) {
        std::cout << "OK SOUTHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHh" << std::endl;
    }
    if(PlCall("goSouth", coord)) {
        std::cout << "CAN GO SOUTHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHh" << std::endl;
    }
    if(PlCall("visited", coordNorth)) {
        std::cout << "VISITED NOOOOOORTH" << std::endl;
    }
    if(PlCall("shootNorth", coord)) {
        return SHOOTNORTH;
    }
    if(PlCall("shootSouth", coord)) {
        return SHOOTSOUTH;
    }
    if(PlCall("shootWest", coord)) {
        return SHOOTWEST;
    }
    if(PlCall("shootEast", coord)) {
        return SHOOTEAST;
    }
    if(PlCall("goNorth", coord)) {
        return GONORTH;
    }
    if(PlCall("goSouth", coord)) {
        return GOSOUTH;
    }
    if(PlCall("goWest", coord)) {
        return GOWEST;
    }
    if(PlCall("goEast", coord)) {
        return GOEAST;
    }
    return DONOTHING;
}

void Player::playRound() {
    this->updateEnvironment();
    int nextMovement = this->getNextMovement();
    switch(nextMovement) {
    case GONORTH:
        m_position.y -= 1;
        break;
    case GOWEST:
        m_position.x -= 1;
        break;
    case GOSOUTH:
        m_position.y += 1;
        break;
    case GOEAST:
        m_position.x += 1;
        break;
    case SHOOTNORTH:
        this->m_map.shoot(m_position.x, m_position.y-1);
        break;
    case SHOOTWEST:
        this->m_map.shoot(m_position.x-1, m_position.y);
        break;
    case SHOOTSOUTH:
        this->m_map.shoot(m_position.x, m_position.y+1);
        break;
    case SHOOTEAST:
        this->m_map.shoot(m_position.x+1, m_position.y);
        break;
    case RUNOUT:
        break;
    default:
        break;
    }

    switch(nextMovement) {
    case RUNOUT:
        if(this->m_map.getCase(m_position.x, m_position.y).portal) {
            std::cout << "Go out" << std::endl;
            score += 10*(m_map.size()*m_map.size());
            score -= 1; //Mouvement
        }
        else {
            std::cout << "Can't go out" << std::endl;
        }
        //TODO go to next level
        break;
    case GONORTH:
    case GOWEST:
    case GOSOUTH:
    case GOEAST:
        score -= 1;
        if(this->m_map.getCase(m_position.x, m_position.y).monster ||
        this->m_map.getCase(m_position.x, m_position.y).hole) {
            score -= 10*(m_map.size()*m_map.size());
            std::cout << "Player is dead" << std::endl;
            m_position.x = 0; m_position.y = 0;
        }
        break;
    case SHOOTNORTH:
    case SHOOTWEST:
    case SHOOTSOUTH:
    case SHOOTEAST:
        score -= 10;
        break;
    default:
        break;
    }
}
