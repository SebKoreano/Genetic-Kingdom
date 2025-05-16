#include "TowerPlacementManager.hpp"
#include "ArcherTower.hpp"   
#include "MageTower.hpp"     
#include "ArtilleryTower.hpp" 
#include "Towers.hpp"  

TowerPlacementManager::TowerPlacementManager(float cellSize, const sf::Font& font)
    : cellSize(cellSize)
{
    // Configurar botones (tres cuadrados horizontales)
    float x0 = 10.f;
    float y0 = 10.f;
    auto makeBtn = [&](Button& b, const sf::Color& color, const std::string& lbl, float offsetX) {
        b.rect.setSize({ (float)buttonSize, (float)buttonSize });
        b.rect.setFillColor(color);
        b.rect.setPosition(sf::Vector2f(x0 + offsetX, y0));
        b.label = lbl;
        };
    makeBtn(btnArcher, sf::Color(139, 69, 19), "Arqueros", 0.f);        // café claro
    makeBtn(btnMage, sf::Color(128, 0, 128), "Magos", buttonSize + 10.f); // morado
    makeBtn(btnArtillery, sf::Color::Black, "Artilleros", 2 * (buttonSize + 10.f));
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
        return nullptr; // clic fuera de botones, ignorar
    }
    active = false;
    return tower;
}

void TowerPlacementManager::draw(sf::RenderWindow& window) const {
    if (!active) return;
    window.draw(btnArcher.rect);
    window.draw(btnMage.rect);
    window.draw(btnArtillery.rect);
    // Opcional: dibujar labels con texto en cada rect
}

bool TowerPlacementManager::isActive() const { return active; }