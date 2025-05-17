#pragma once
#include <SFML/Graphics.hpp>
#include "GridMap.hpp"
#include "Player.hpp"
#include "WaveManager.hpp"
#include "TowerPlacementManager.hpp"
#include <vector>
#include "Bullet.hpp"


/// Controlador principal del juego: orquesta mapa, oleadas, jugador y torres
class GameController {
public:
    GameController(sf::RenderWindow& window,
        int rows,
        int cols,
        float cellSize,
        const sf::Font& font);

    /// Inicia el loop principal
    void run();
    std::vector<Tower*>   towers;
    std::vector<Bullet>   bullets;

private:
    sf::RenderWindow& window;
    GridMap map;
    Player player;
    WaveManager waveMgr;
    TowerPlacementManager placementMgr;

    // Textos UI
    sf::Text goldText;
    sf::Text livesText;

    // Para manejo de input
    int selectedRow = -1;
    int selectedCol = -1;

    sf::Clock clock;

    void handleEvent(const sf::Event* ev);
    void update(float dt);
    void draw();
};