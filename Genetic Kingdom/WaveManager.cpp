#include "WaveManager.hpp"
#include <cstdlib>
#include <ctime>
#include <sstream>

WaveManager::WaveManager(GridMap& map, float cellSize, float speed,
    int minEnemies, int maxEnemies,
    const sf::Font& font, float spawnInterval)
    : map(map), cellSize(cellSize), speed(speed),
    minEnemies(minEnemies), maxEnemies(maxEnemies),
    spawnCount(0), spawnedCount(0), waveNumber(1),
    enemies(10), waveText(font),
    spawnInterval(spawnInterval), spawnTimer(spawnInterval)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    waveText.setCharacterSize(24);
    waveText.setFillColor(sf::Color::White);
    waveText.setString("");
    waveText.setPosition({
        5.f,
        map.getStartPosition().y * cellSize + (map.getGoalPosition().y + 1) * cellSize + 5.f
        });
    spawnWave();
}

void WaveManager::spawnWave() {
    enemies.clear();
    spawnCount = std::rand() % (maxEnemies - minEnemies + 1) + minEnemies;
    spawnedCount = 0;
    spawnTimer = spawnInterval;
}

void WaveManager::handleClick(int x, int y) {
    int col = x / static_cast<int>(cellSize), row = y / static_cast<int>(cellSize);
    if (col >= 0 && col < map.getCols() && row >= 0 && row < map.getRows()) {
        map.toggleWalkable(row, col);
        if (map.isPathAvailable()) {
            for (int i = 0;i < enemies.size();++i) enemies.get(i)->resetPath();
        }
        else map.toggleWalkable(row, col);
    }
}

void WaveManager::update(float dt) {
    spawnTimer += dt;
    if (spawnedCount < spawnCount && spawnTimer >= spawnInterval) {
        spawnTimer -= spawnInterval;
        enemies.push(new Enemy(map, cellSize, speed));
        ++spawnedCount;
    }
    for (int i = 0;i < enemies.size();++i) enemies.get(i)->update(dt);
    for (int i = 0;i < enemies.size();) {
        if (!enemies.get(i)->isAlive()) enemies.removeAt(i);
        else ++i;
    }
    if (spawnedCount >= spawnCount && enemies.size() == 0) {
        ++waveNumber;
        spawnWave();
    }
}

void WaveManager::draw(sf::RenderWindow& window) {
    for (int i = 0;i < enemies.size();++i) enemies.get(i)->draw(window);
    std::ostringstream ss;
    ss << "Oleada: " << waveNumber;
    waveText.setString(ss.str());
    window.draw(waveText);
}