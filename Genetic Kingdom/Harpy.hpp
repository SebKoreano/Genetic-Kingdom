#pragma once  
#include "Enemy.hpp"  

class Harpy : public Enemy {
public:
    Harpy(GridMap& m, float cellSize, float speed)
        : Enemy(m, cellSize, speed) {
        health = 100.f;
        arrowResist = 0.0f;
        magicResist = 0.0f;
        artilleryResist = 0.5f;
        setColor(sf::Color(139, 69, 19));
        this->speed = 50.f;
        goldDrop = 30;
    }
};
