#pragma once
#include <SFML/Graphics.hpp>
#include "GridMap.hpp"
#include "Player.hpp"
#include "WaveManager.hpp"
#include "TowerPlacementManager.hpp"
#include "SimpleVector.hpp"
#include "Bullet.hpp"
#include "TowerUpgradeManager.hpp"

class GameController {
public:
    GameController(sf::RenderWindow& window,int rows, int cols, float cellSize, const sf::Font& font);
    void run();
    SimpleVector<Tower*> towers;
    SimpleVector<Bullet> bullets;
private:
    TowerUpgradeManager upgradeMgr;
    sf::RenderWindow& window;
    GridMap map;
    Player player;
    WaveManager waveMgr;
    TowerPlacementManager placementMgr;
    sf::Text goldText, livesText, gameOverText;
    sf::RectangleShape gameOverBackground;
    bool gameOver;
    int selectedRow = -1, selectedCol = -1;
    sf::Clock clock;
    void handleEvent(const sf::Event* ev);
    void update(float dt);
    void draw();
};