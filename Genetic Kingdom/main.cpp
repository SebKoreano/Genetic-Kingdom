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

	window.setFramerateLimit(60);

    GridMap map(gridRows, gridCols, cellSize);
    Enemy enemy(map, cellSize, 120.f);
    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        // Procesar eventos usando la nueva API de SFML 3.0
        while (auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>())
                window.close();
        }

        // Actualizar
        enemy.update(dt);

        // Renderizar
        window.clear();
        map.draw(window);
        enemy.draw(window);
        window.display();
    }

    return 0;
}
