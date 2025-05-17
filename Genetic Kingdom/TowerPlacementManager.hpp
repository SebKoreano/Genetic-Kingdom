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
    const sf::Font& font;

    struct Button {
        sf::RectangleShape rect;
        sf::Text text;
        // Constructor que inicializa el texto con la fuente
        Button(const sf::Font& font)
            : text(font) {
        }
    };

    Button btnArcher;
    Button btnMage;
    Button btnArtillery;


    // Fondo semitransparente
    sf::RectangleShape background;
};