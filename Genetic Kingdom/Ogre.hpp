#pragma once  
#include "Enemy.hpp"  

class Ogre : public Enemy {  
public:  
    Ogre(GridMap& map, float cellSize, float speed)
        : Enemy(map, cellSize, speed)
    {
        health = 140.f;
        arrowResist = 0.2f;
        magicResist = 0.1f;
        artilleryResist = 0.3f;
        //setColor({ 0,100,0 });
        this->speed = 50.f;
    }
};
 

