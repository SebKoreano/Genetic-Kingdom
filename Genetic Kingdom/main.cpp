#include <SFML/Graphics.hpp>
#include "GridMap.hpp"
#include "WaveManager.hpp"

int main() {
    constexpr int gridRows = 15, gridCols = 20;
    const float cellSize = 40.f, speed = 120.f;
    const int minEnemies = 5, maxEnemies = 10;

    int width = gridCols * static_cast<int>(cellSize);
    int height = gridRows * static_cast<int>(cellSize) + 50;
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Tower Defense");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("Nexa-Heavy.ttf")) {
        // error cargar fuente
    }

    GridMap map(gridRows, gridCols, cellSize);
    WaveManager waveMgr(map, cellSize, speed, minEnemies, maxEnemies, font);
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        while (auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) window.close();
            else if (const auto* mb = ev->getIf<sf::Event::MouseButtonPressed>()) {
                if (mb->button == sf::Mouse::Button::Left)
                    waveMgr.handleClick(mb->position.x, mb->position.y);
            }
        }
        waveMgr.update(dt);
        window.clear();
        map.draw(window);
        waveMgr.draw(window);
        window.display();
    }

	return 0;
}