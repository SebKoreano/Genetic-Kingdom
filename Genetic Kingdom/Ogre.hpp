#pragma once  
#include "Enemy.hpp"  

class Ogre : public Enemy {  
public:  
   Ogre(GridMap& m, float cellSize, float speed)  
       : Enemy(m, cellSize, speed) {  
       maxHealth = 200.f;  
       currentHealth = maxHealth;  
       this->speed = 50.f;    // lento  
       resistArrow = 0.8f;     // 80% de daño recibido  
       resistMagic = 0.3f;     // 30% de daño recibido  
       resistArtillery = 0.3f;  
   }  
};
