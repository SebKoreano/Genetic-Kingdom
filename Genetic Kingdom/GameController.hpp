#pragma once
#include <SFML/Graphics.hpp>
#include "GridMap.hpp"
#include "Player.hpp"
#include "WaveManager.hpp"
#include "TowerPlacementManager.hpp"
#include <vector>

class GameController {
public:
    GameController(sf::RenderWindow& window, int rows, int cols, float cellSize);
    void run();

private:
    sf::RenderWindow& window;
    GridMap map;
    Player player;
    WaveManager waveMgr;
    TowerPlacementManager placementMgr;
    std::vector<Tower*> towers;
    sf::Font font;
    sf::Clock clock;

    int selectedRow = -1;
    int selectedCol = -1;

    void handleEvent(const sf::Event* ev);
    void update(float dt);
    void draw();
};