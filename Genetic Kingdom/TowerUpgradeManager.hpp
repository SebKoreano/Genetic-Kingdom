#pragma once
#include <SFML/Graphics.hpp>
#include "Towers.hpp"

/// Administra el popup de mejora de torres
class TowerUpgradeManager {
public:
    TowerUpgradeManager(float windowWidth, float windowHeight, const sf::Font& font);

    // Solicita abrir popup para esta torre; retorna true si tower puede mejorar
    bool requestUpgrade(Tower* tower);

    // Procesa clic; retorna 1=Sí, 0=No, -1=Ignorar
    int processClick(int mouseX, int mouseY);

    // Dibuja el popup si está activo
    void draw(sf::RenderWindow& window) const;

    bool isActive() const { return active; }

private:
    const sf::Font& font;
    bool active;
    Tower* tower;

    sf::RectangleShape overlay;    // fondo semitransparente
    sf::RectangleShape panel;      // panel central
    sf::Text popupText;            // texto "Mejorar? $X"

    sf::RectangleShape btnYes;
    sf::Text textYes;
    sf::RectangleShape btnNo;
    sf::Text textNo;
};