#pragma once
#include <SFML/Graphics.hpp>
#include "Towers.hpp"

/// Maneja la UI para seleccionar tipo de torre en un celda
class TowerPlacementManager {
public:
    TowerPlacementManager(float cellSize, const sf::Font& font);
    bool requestPlacement(int row, int col);
    Tower* processClick(int mouseX, int mouseY);
    void draw(sf::RenderWindow& window) const;
    bool isActive() const;
    float getCellSize() const { return cellSize; }

private:
    float cellSize;
    const int buttonSize = 50;
    sf::Vector2i cell;
    bool active = false;
    struct Button { sf::RectangleShape rect; std::string label; };
    Button btnArcher, btnMage, btnArtillery;
};