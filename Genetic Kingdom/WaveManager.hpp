#pragma once
#include <SFML/Graphics.hpp>
#include "GridMap.hpp"
#include "EnemyArray.hpp"

class WaveManager {
public:
    WaveManager(GridMap& map, float cellSize, float speed,
        int* waveSizes, int waveCount, const sf::Font& font);
    void handleClick(int x, int y);
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    GridMap& map;
    float cellSize;
    float speed;
    int* waveSizes;
    int waveCount;
    int currentWave;
    EnemyArray enemies;
    sf::Text waveText;

    void spawnWave();
};