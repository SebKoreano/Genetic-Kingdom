#pragma once
#include <SFML/Graphics.hpp>
#include "GridMap.hpp"

class Enemy {
public:
    Enemy(int startRow, int startCol, float cellSize);

    virtual void update(); 
    void draw(sf::RenderWindow& window);

protected:
    sf::RectangleShape shape;
    int currentRow, currentCol;
};
