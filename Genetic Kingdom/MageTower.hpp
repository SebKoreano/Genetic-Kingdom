#pragma once
#include "Towers.hpp" 

class MageTower : public Tower {
public:
    MageTower(float cellSize, int row, int col)
        : Tower(/*cost=*/100,
            /*range=*/3.f,
            /*damage=*/40,
            /*reloadTime=*/1.0f,
            cellSize, row, col)
    {
        shape.setFillColor(sf::Color::Cyan);
    }
};