#pragma once  
#include "Enemy.hpp" 

class Mercenary : public Enemy {
public:
    Mercenary(GridMap& m, float cellSize, float speed)
        : Enemy(m, cellSize, speed) {
        health = 110.f;
        arrowResist = 0.8f;
        magicResist = 0.3f;
        artilleryResist = 0.8f;
        setColor(sf::Color(128, 128, 128));
        this->speed = 70.f;
        goldDrop = 40;
    }
};
