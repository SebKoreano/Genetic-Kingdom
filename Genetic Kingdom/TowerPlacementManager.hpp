#pragma once
#include <SFML/Graphics.hpp>
#include "Towers.hpp"  
#include "ArcherTower.hpp"   
#include "MageTower.hpp"     
#include "ArtilleryTower.hpp" 
#include "Towers.hpp"

/// Maneja la UI para seleccionar tipo de torre en un celda
class TowerPlacementManager {
public:
    TowerPlacementManager(float cellSize, const sf::Font& font);

    // Llamado al hacer clic en la grilla. Retorna true si abre el selector
    bool requestPlacement(int row, int col);

    // Maneja eventos de clic cuando el selector est� visible
    // Retorna un puntero a Tower si se complet� selecci�n, nullptr si sigue abierto
    Tower* processClick(int mouseX, int mouseY);

    // Dibuja el panel de selecci�n
    void draw(sf::RenderWindow& window) const;

    bool isActive() const;

    /// Devuelve el tama�o de celda, para calcular columnas/filas desde coordenadas
    float getCellSize() const { return cellSize; }


private:
    float cellSize;
    const int buttonSize = 50;
    sf::Vector2i cell;          // Celda donde colocar
    bool active = false;

    // Botones: rect�ngulos y sus labels
    struct Button { sf::RectangleShape rect; std::string label; };
    Button btnArcher, btnMage, btnArtillery;
};