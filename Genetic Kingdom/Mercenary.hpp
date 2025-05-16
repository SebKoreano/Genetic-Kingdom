#pragma once  
#include "Enemy.hpp" 

class Mercenary : public Enemy {
public:
    Mercenary(GridMap& m, float cellSize, float speed)
        : Enemy(m, cellSize, speed) {
        maxHealth = 150.f;
        currentHealth = maxHealth;
        this->speed = 120.f;     // intermedio
        resistArrow = 0.8f;
        resistMagic = 0.3f;
        resistArtillery = 0.8f;
    }
};
