#include "Player.hpp"
#include <iostream>
#include <string>
#include <random>

Player::Player(Map& map) : m_map(map) {
    this->initNextRound();
}

void Player::updateEnvironment() {
    PlTermv coord(2);
    coord[0] = (long)m_position.x;
    coord[1] = (long)m_position.y;
    const std::string pos_string = std::to_string(m_position.x) + "," + std::to_string(m_position.y);
    const char* pos = pos_string.c_str();

    PlTermv k(1);
    //If we detect light
    if(m_map(m_position.x, m_position.y).portal) {
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
        PlCall("setPoop", coord);
    }
    if(m_map(m_position.x, m_position.y - 1).walkable) {
        PlTermv argWalk(2);
        argWalk[0] = (long)m_position.x;
        argWalk[1] = (long)(m_position.y-1);
        PlCall("setWalkable", argWalk);
    }
    if(m_map(m_position.x, m_position.y + 1).walkable) {
        PlTermv argWalk(2);
        argWalk[0] = (long)m_position.x;
        argWalk[1] = (long)(m_position.y+1);
        PlCall("setWalkable", argWalk);
    }
    if(m_map(m_position.x - 1, m_position.y).walkable) {
        PlTermv argWalk(2);
        argWalk[0] = (long)(m_position.x-1);
        argWalk[1] = (long)m_position.y;
        PlCall("setWalkable", argWalk);
    }
    if(m_map(m_position.x + 1, m_position.y).walkable) {
        PlTermv argWalk(2);
        argWalk[0] = (long)(m_position.x+1);
        argWalk[1] = (long)m_position.y;
        PlCall("setWalkable", argWalk);
    }
    PlCall("setVisited", coord);
}

Movement Player::getNextMovement() {
    PlTermv coord(2);
    coord[0] = (long)m_position.x;
    coord[1] = (long)m_position.y;
    PlTermv coordsouth(2);
    coordsouth[0] = (long)m_position.x;
    coordsouth[1] = (long)(m_position.y+1);
    PlTermv coordNorth(2);
    coordNorth[0] = (long)m_position.x;
    coordNorth[1] = (long)m_position.y-1;

    //If we find the portal
    if(PlCall("runOut", coord)) {
        return RUNOUT;
    }

    //If we can shoot
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

    //Else, move
    if(PlCall("betterNorth", coord)) {
        return GONORTH;
    }
    if(PlCall("betterSouth", coord)) {
        return GOSOUTH;
    }
    if(PlCall("betterWest", coord)) {
        return GOWEST;
    }
    if(PlCall("betterEast", coord)) {
        return GOEAST;
    }

    std::vector<int> canMove;
    if(PlCall("goNorth", coord)) {
        canMove.push_back(0);
    }
    if(PlCall("goSouth", coord)) {
        canMove.push_back(1);
    }
    if(PlCall("goWest", coord)) {
        canMove.push_back(2);
    }
    if(PlCall("goEast", coord)) {
        canMove.push_back(3);
    }

    if(canMove.size() > 0) {
        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(0, canMove.size()-1);
        int m = uniform_dist(e1);
        switch (canMove.at(m))
        {
        case 0:
            return GONORTH;
            break;
        case 1:
            return GOSOUTH;
            break;
        case 2:
            return GOWEST;
            break;
        case 3:
            return GOEAST;
            break;
        default:
            /* code */
            break;
        }
    }

    //Last try
    if(PlCall("goDieInNorth", coord)) {
        return GONORTH;
    }
    if(PlCall("goDieInSouth", coord)) {
        return GOSOUTH;
    }
    if(PlCall("goDieInWest", coord)) {
        return GOWEST;
    }
    if(PlCall("goDieInEast", coord)) {
        return GOEAST;
    }

    //Blocked
    return DONOTHING;
}

void Player::playRound() {
    this->updateEnvironment();
    //Make an action
    int nextMovement = this->getNextMovement();
    std::cout << "Player at pos (" << m_position.x << ";" << m_position.y << ")" << std::endl;
    switch(nextMovement) {
    case GONORTH:
        std::cout << "[GONORTH]" << std::endl;
        m_position.y -= 1;
        break;
    case GOWEST:
        std::cout << "[GOWEST]" << std::endl;
        m_position.x -= 1;
        break;
    case GOSOUTH:
        std::cout << "[GOSOUTH]" << std::endl;
        m_position.y += 1;
        break;
    case GOEAST:
        std::cout << "[GOEAST]" << std::endl;
        m_position.x += 1;
        break;
    case SHOOTNORTH:
        std::cout << "[SHOOTNORTH]" << std::endl;
        this->m_map.shoot(m_position.x, m_position.y-1);
        break;
    case SHOOTWEST:
        std::cout << "[SHOOTWEST]" << std::endl;
        this->m_map.shoot(m_position.x-1, m_position.y);
        break;
    case SHOOTSOUTH:
        std::cout << "[SHOOTSOUTH]" << std::endl;
        this->m_map.shoot(m_position.x, m_position.y+1);
        break;
    case SHOOTEAST:
        std::cout << "[SHOOTEAST]" << std::endl;
        this->m_map.shoot(m_position.x+1, m_position.y);
        break;
    case RUNOUT:
        std::cout << "[RUNOUT]" << std::endl;
        break;
    default:
        std::cout << "[DONOTHING]" << std::endl;
        break;
    }

    switch(nextMovement) {
    case RUNOUT:
        if(this->m_map(m_position.x, m_position.y).portal) {
            score += 10*(m_map.size()*m_map.size());
            score -= 1; //Mouvement
            b_hasWin = true;
            std::cout << "Current score : " << score << std::endl;
        }
        else {
            std::cout << "Can't go out" << std::endl;
        }
        break;
    case GONORTH:
    case GOWEST:
    case GOSOUTH:
    case GOEAST:
        score -= 1;
        if(this->m_map(m_position.x, m_position.y).monster ||
        this->m_map(m_position.x, m_position.y).hole) {

            PlTermv argHole(2);
            argHole[0] = (long)m_position.x;
            argHole[1] = (long)m_position.y;
            PlCall("setVisited", argHole);
            PlCall("setHole", argHole);

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

void Player::initNextRound() {
    m_position.x = 0;
    m_position.y = 0;
    b_hasWin = false;
    score = 0;
}
