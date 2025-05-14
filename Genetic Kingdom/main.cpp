#include <SFML/Graphics.hpp>
#include "GridMap.hpp"
#include "Enemy.hpp"

constexpr int windowWidth = 800;
constexpr int windowHeight = 800;
constexpr int gridCols = 20;
constexpr int gridRows = 15;
constexpr int gridWidth = 800;
constexpr int gridHeight = 600;
constexpr int cellSize = gridWidth / gridCols;

int main() {
    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Tower Defense Grid");

    GridMap map(gridRows, gridCols, cellSize);
    sf::Vector2i spawnPos = map.getStartPosition();
    Enemy enemy(spawnPos.y, spawnPos.x, cellSize);

    while (window.isOpen()) {
        // Read input
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Update
        enemy.update();

        window.clear();

        // Draw
        map.draw(window);
        enemy.draw(window);

        window.display();
    }

    return 0;
}
