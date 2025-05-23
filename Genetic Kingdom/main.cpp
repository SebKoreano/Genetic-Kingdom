#include <SFML/Graphics.hpp>
#include "GameController.hpp"

int main() {
    constexpr int gridRows = 15, gridCols = 20;
    const float cellSize = 40.f;
    sf::RenderWindow window(sf::VideoMode({ static_cast<unsigned int>(gridCols * cellSize),static_cast<unsigned int>(gridRows * cellSize + 50) }),"Tower Defense");
    sf::Font font;
    if (!font.openFromFile("Nexa-Heavy.ttf")) {
        // manejar error
    }
    GameController game(window, gridRows, gridCols, cellSize, font);
    game.run();
    return 0;
}