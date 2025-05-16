#pragma once  
#include "Enemy.hpp"  

class DarkElf : public Enemy {  
public:  
  DarkElf(GridMap& m, float cellSize, float speed)
      : Enemy(m, cellSize, speed) {
      this->maxHealth = 120.f;  
      this->currentHealth = maxHealth;  
      this->speed = 150.f;    // muy rápido  
      this->resistArrow = 0.3f;  
      this->resistMagic = 0.8f;  
      this->resistArtillery = 0.3f;  
  }  
};
