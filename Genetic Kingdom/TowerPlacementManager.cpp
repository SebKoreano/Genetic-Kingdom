#include "TowerPlacementManager.hpp"

TowerPlacementManager::TowerPlacementManager(float cellSize, const sf::Font& font)
    : cellSize(cellSize)
    , font(font)
    , btnArcher(font)
    , btnMage(font)
    , btnArtillery(font)
{
    float x0 = 10.f, y0 = 10.f;
    // Botones
    auto makeBtn = [&](Button& b, const sf::Color& color,
        const std::string& lbl, int cost, float offsetX) {
            b.rect.setSize({ (float)buttonSize, (float)buttonSize });
            b.rect.setFillColor(color);
            b.rect.setPosition(sf::Vector2f(x0 + offsetX, y0));
            // Texto con nombre y costo
            b.text.setFont(font);
            b.text.setString(lbl + " ($" + std::to_string(cost) + ")");
            b.text.setCharacterSize(14);
            b.text.setFillColor(sf::Color::White);
            // Centrar debajo del botón
            auto bounds = b.text.getLocalBounds();
            float textWidth = bounds.size.x;
            b.text.setPosition(sf::Vector2f(x0 + offsetX + (buttonSize - textWidth) / 2.f, y0 + buttonSize + 5.f));

        };
    makeBtn(btnArcher, sf::Color(139, 69, 19), "Arqueros", 50, 30.f);
    makeBtn(btnMage, sf::Color(128, 0, 128), "Magos", 100, buttonSize + 110.f);
    makeBtn(btnArtillery, sf::Color::Black, "Artilleros", 150, 2 * (buttonSize + 100.f));

    // Fondo gris semitransparente
    background.setFillColor(sf::Color(50, 50, 50, 200));
}

bool TowerPlacementManager::requestPlacement(int row, int col) {
    cell = { col, row };
    active = true;
    return active;
}

Tower* TowerPlacementManager::processClick(int mouseX, int mouseY) {
    if (!active) return nullptr;
    sf::Vector2f pt((float)mouseX, (float)mouseY);
    Tower* tower = nullptr;
    if (btnArcher.rect.getGlobalBounds().contains(pt)) {
        tower = new ArcherTower(cellSize, cell.y, cell.x);
    }
    else if (btnMage.rect.getGlobalBounds().contains(pt)) {
        tower = new MageTower(cellSize, cell.y, cell.x);
    }
    else if (btnArtillery.rect.getGlobalBounds().contains(pt)) {
        tower = new ArtilleryTower(cellSize, cell.y, cell.x);
    }
    else {
        return nullptr;
    }
    active = false;
    return tower;
}

void TowerPlacementManager::draw(sf::RenderWindow& window) const {  
   if (!active) return;  
   // Crear una copia mutable del fondo para modificar su tamaño  
   sf::RectangleShape mutableBackground = background;  
   mutableBackground.setSize(sf::Vector2f(window.getSize()));  
   mutableBackground.setPosition(sf::Vector2f(0.f, 0.f));  
   window.draw(mutableBackground);  
   // Dibujar botones y textos  
   window.draw(btnArcher.rect);  
   window.draw(btnMage.rect);  
   window.draw(btnArtillery.rect);  
   window.draw(btnArcher.text);  
   window.draw(btnMage.text);  
   window.draw(btnArtillery.text);  
}

bool TowerPlacementManager::isActive() const {
    return active;
}