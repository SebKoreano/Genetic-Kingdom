#pragma once  
#include "Enemy.hpp"  

class Harpy : public Enemy {
public:
    Harpy(GridMap& m, float cellSize, float speed)
        : Enemy(m, cellSize, speed) {
        maxHealth = 100.f;
        currentHealth = maxHealth;
        this->speed = 100.f;    // media
        resistArrow = 0.0f;     // solo magia/arqueros
        resistMagic = 0.0f;
        resistArtillery = 0.5f;
    }
};
