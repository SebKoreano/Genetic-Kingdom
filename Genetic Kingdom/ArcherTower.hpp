#pragma once
#include "Towers.hpp" 

class ArcherTower : public Tower {
public:
   ArcherTower(float cellSize, int row, int col)
       : Tower(/*cost=*/ 50,
           /*range=*/ 5.f,
           /*damage=*/30,
           /*reloadTime=*/0.5f,
           cellSize, row, col)
   {
       shape.setFillColor(sf::Color::Green);
   }
};