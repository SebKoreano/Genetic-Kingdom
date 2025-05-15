#pragma once
#include <SFML/Graphics.hpp>
#include "GridMap.hpp"
#include "EnemyArray.hpp"

class WaveManager {
public:
    WaveManager(GridMap& map, float cellSize, float speed,
        int minEnemies, int maxEnemies,
        const sf::Font& font, float spawnInterval = 0.5f);
    void handleClick(int x, int y);
    void update(float dt);
    void draw(sf::RenderWindow& window);
private:
    GridMap& map;
    float cellSize, speed;
    int minEnemies, maxEnemies, spawnCount, spawnedCount, waveNumber;
    EnemyArray enemies;
    sf::Text waveText;
    float spawnInterval, spawnTimer;
    void spawnWave();
};