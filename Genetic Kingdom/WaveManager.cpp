#include "WaveManager.hpp"
#include <sstream>

WaveManager::WaveManager(GridMap& map, float cellSize, float speed,
    int* waveSizes, int waveCount, const sf::Font& font)
    : map(map)
    , cellSize(cellSize)
    , speed(speed)
    , waveSizes(waveSizes)
    , waveCount(waveCount)
    , currentWave(0)
    , enemies(10)
    , waveText(font)
{
    // Configurar texto de oleada
    waveText.setCharacterSize(24);
    waveText.setFillColor(sf::Color::White);
    waveText.setString("");
    waveText.setPosition(
        sf::Vector2f(
            5.f,
            map.getStartPosition().y * cellSize + (map.getGoalPosition().y + 1) * cellSize + 5.f
        )
    );
    spawnWave();
}

void WaveManager::handleClick(int x, int y) {
    int col = x / static_cast<int>(cellSize);
    int row = y / static_cast<int>(cellSize);
    if (col >= 0 && col <= map.getGoalPosition().x && row >= 0 && row <= map.getGoalPosition().y) {
        map.toggleWalkable(row, col);
        if (map.isPathAvailable()) {
            for (int i = 0; i < enemies.size(); ++i)
                enemies.get(i)->resetPath();
        }
        else {
            map.toggleWalkable(row, col);
        }
    }
}

void WaveManager::update(float dt) {
    for (int i = 0; i < enemies.size(); ++i)
        enemies.get(i)->update(dt);
    for (int i = 0; i < enemies.size(); ) {
        if (!enemies.get(i)->isAlive()) enemies.removeAt(i);
        else ++i;
    }
    if (enemies.size() == 0) {
        currentWave = (currentWave + 1) % waveCount;
        spawnWave();
    }
}

void WaveManager::draw(sf::RenderWindow& window) {
    for (int i = 0; i < enemies.size(); ++i)
        enemies.get(i)->draw(window);
    std::ostringstream ss;
    ss << "Oleada: " << (currentWave + 1);
    waveText.setString(ss.str());
    window.draw(waveText);
}

void WaveManager::spawnWave() {
    enemies.clear();
    int count = waveSizes[currentWave];
    for (int i = 0; i < count; ++i) {
        Enemy* e = new Enemy(map, cellSize, speed);
        enemies.push(e);
    }
}