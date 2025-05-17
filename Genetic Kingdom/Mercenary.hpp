#pragma once  
#include "Enemy.hpp" 

class Mercenary : public Enemy {
public:
    Mercenary(GridMap& m, float cellSize, float speed)
        : Enemy(m, cellSize, speed) {
        health = 150.f;
        arrowResist = 0.8f;
        magicResist = 0.3f;
        artilleryResist = 0.8f;
        //setColor({ 0,100,0 });
        this->speed = 120.f;
    }
};
