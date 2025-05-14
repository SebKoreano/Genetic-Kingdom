#include "Enemy.hpp"

Enemy::Enemy(int startRow, int startCol, float cellSize)
    : currentRow(startRow), currentCol(startCol)
{
    shape.setSize({ cellSize * 0.8f, cellSize * 0.8f });
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(sf::Vector2f{
        startCol * cellSize + cellSize * 0.1f,
        startRow * cellSize + cellSize * 0.1f
    });


}

void Enemy::update()
{
    // Movimiento futuro
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::Vector2i GridMap::getStartPosition() const {
    return start;
}

sf::Vector2i GridMap::getGoalPosition() const {
    return goal;
}

