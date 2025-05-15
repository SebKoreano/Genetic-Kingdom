#include <SFML/Graphics.hpp>
#include "GridMap.hpp"
#include "WaveManager.hpp"

int main() {
    constexpr int gridRows = 15, gridCols = 20;
    const float cellSize = 40.f, speed = 120.f;
    int waveSizesArray[] = { 5, 10, 15 };
    int waveCount = sizeof(waveSizesArray) / sizeof(int);

    int windowWidth = gridCols * static_cast<int>(cellSize);
    int windowHeight = gridRows * static_cast<int>(cellSize) + 50;
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Tower Defense");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("Nexa-Heavy.ttf")) {
        // Manejar error de fuente
    }

    GridMap map(gridRows, gridCols, cellSize);
    WaveManager waveMgr(map, cellSize, speed, waveSizesArray, waveCount, font);
    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            else if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>()) {
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