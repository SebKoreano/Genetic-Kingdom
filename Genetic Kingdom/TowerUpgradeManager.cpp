#include "TowerUpgradeManager.hpp"

TowerUpgradeManager::TowerUpgradeManager(float windowWidth, float windowHeight, const sf::Font& font)
   : font(font)
   , active(false)
   , tower(nullptr)
   , popupText(font)
   , textYes(font)
   , textNo(font)
{
   // Overlay
   overlay.setSize({ windowWidth, windowHeight });
   overlay.setFillColor(sf::Color(50, 50, 50, 200));

   // Panel
   float pw = 300.f, ph = 150.f;
   panel.setSize({ pw, ph });
   panel.setFillColor(sf::Color(30, 30, 30, 230));
   panel.setOrigin(sf::Vector2f(pw / 2.f, ph / 2.f));
   panel.setPosition(sf::Vector2f(windowWidth / 2.f, windowHeight / 2.f));

   // Popup text
   popupText.setFont(font);
   popupText.setCharacterSize(24);
   popupText.setFillColor(sf::Color::White);

   // Botones
   float bw = 80.f, bh = 40.f;
   // Sí
   btnYes.setSize({ bw, bh });
   btnYes.setFillColor(sf::Color::Red);
   btnYes.setOrigin(sf::Vector2f(bw / 2.f, bh / 2.f));
   btnYes.setPosition(sf::Vector2f(windowWidth / 2.f - 60.f, windowHeight / 2.f + ph / 4.f));
   textYes.setFont(font);
   textYes.setString("Sí");
   textYes.setCharacterSize(20);
   textYes.setFillColor(sf::Color::White);
   // No
   btnNo.setSize({ bw, bh });
   btnNo.setFillColor(sf::Color::Red);
   btnNo.setOrigin(sf::Vector2f(bw / 2.f, bh / 2.f));
   btnNo.setPosition(sf::Vector2f(windowWidth / 2.f + 60.f, windowHeight / 2.f + ph / 4.f));
   textNo.setFont(font);
   textNo.setString("No");
   textNo.setCharacterSize(20);
   textNo.setFillColor(sf::Color::White);
}

bool TowerUpgradeManager::requestUpgrade(Tower* t) {
    if (!t || !t->canUpgrade()) return false;
    tower = t;
    active = true;
    int price = tower->getUpgradeCost();
    popupText.setString("Mejorar? $" + std::to_string(price));

    // Centrar popupText en el panel
    auto pb = popupText.getLocalBounds();
    popupText.setOrigin(sf::Vector2f(pb.size.x / 2.f, pb.size.y / 2.f));
    popupText.setPosition(sf::Vector2f(panel.getPosition().x, panel.getPosition().y - panel.getSize().y / 4.f));

    // Centrar texto de botón Sí
    auto tyb = textYes.getLocalBounds();
    textYes.setOrigin(sf::Vector2f(tyb.size.x / 2.f, tyb.size.y / 2.f));
    textYes.setPosition(btnYes.getPosition());

    // Centrar texto de botón No
    auto tnb = textNo.getLocalBounds();
    textNo.setOrigin(sf::Vector2f(tnb.size.x / 2.f, tnb.size.y / 2.f));
    textNo.setPosition(btnNo.getPosition());

    return true;
}

int TowerUpgradeManager::processClick(int mouseX, int mouseY) {
    if (!active) return -1;
    sf::Vector2f pt((float)mouseX, (float)mouseY);

    int result = 0; // por defecto cancelar mejora
    if (btnYes.getGlobalBounds().contains(pt)) result = 1;
    // btnNo (o clic fuera) result=0

    active = false;      
    return result;
}


void TowerUpgradeManager::draw(sf::RenderWindow& window) const {
   if (!active) return;
   window.draw(overlay);
   window.draw(panel);
   window.draw(popupText);
   window.draw(btnYes);
   window.draw(btnNo);
   window.draw(textYes);
   window.draw(textNo);
}