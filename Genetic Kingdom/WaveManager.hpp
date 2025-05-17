#pragma once
#include <SFML/Graphics.hpp>
#include "GridMap.hpp"
#include "EnemyArray.hpp"
#include "Player.hpp"

class WaveManager {
public:
    WaveManager(GridMap& map, float cellSize, float speed,
        int minEnemies, int maxEnemies,
        const sf::Font& font, float spawnInterval = 0.5f);
    void handleClick(int x, int y);
    void update(float dt, Player& player);
    void draw(sf::RenderWindow& window);
    /// Fuerza a todos los enemigos activos a recálcular su ruta
    void resetAllEnemyPaths();
    std::vector<Enemy*> getEnemyList() const {
        std::vector<Enemy*> out;
        for (int i = 0;i < enemies.size();++i)
            out.push_back(enemies.get(i));
        return out;
    }
private:
    GridMap& map;
    float cellSize, speed;
    int minEnemies, maxEnemies, spawnCount, spawnedCount, waveNumber;
    EnemyArray enemies;
    sf::Text waveText;
    float spawnInterval, spawnTimer;
    void spawnWave();
};