#pragma once

#include "Map.hpp"
#include "Position.hpp"
#include <SWI-cpp.h>
#include <vector>

enum Movement {
  RUNOUT,
  GONORTH,
  GOWEST,
  GOSOUTH,
  GOEAST,
  SHOOTNORTH,
  SHOOTWEST,
  SHOOTSOUTH,
  SHOOTEAST,
  DONOTHING
};

class Player {
public:
  Player(Map &map);
  Position getPosition() { return m_position; }
  Map &getMap() { return m_map; };

  void updateEnvironment();
  void initNextRound();
  void playRound();
  int getScore() { return score; };
  bool hasWin() { return b_hasWin; }

private:
  // Attributes
  Position m_position;
  Map &m_map;
  int score;
  bool b_hasWin;
  // Return next action
  Movement getNextMovement();
};
