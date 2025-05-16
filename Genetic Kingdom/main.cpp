#include <SFML/Graphics.hpp>  
#include "GameController.hpp"  

int main() {  
   sf::RenderWindow window(sf::VideoMode({ 800, 650 }), "Tower Defense");  
   GameController game(window, 15, 20, 40.0f); // Added rows, cols, and cellSize arguments  
   game.run();  
   return 0;  
}