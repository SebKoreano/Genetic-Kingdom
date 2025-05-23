#pragma once  
#include "Enemy.hpp"  

class DarkElf : public Enemy {  
public:  
  DarkElf(GridMap& m, float cellSize, float speed)
      : Enemy(m, cellSize, speed) {

      health = 90.f;
      arrowResist = 0.3f;
      magicResist = 0.8f;
      artilleryResist = 0.3f;
      //setColor({ 0,100,0 });
      this->speed = 70.f;
      goldDrop = 50;
  }  
};
