#include "WaveManager.hpp"
#include "Ogre.hpp"      
#include "DarkElf.hpp"   
#include "Harpy.hpp"     
#include "Mercenary.hpp" 
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "GameController.hpp"

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

void WaveManager::update(float dt, Player& player) {
    spawnTimer += dt;
    if (spawnedCount < spawnCount && spawnTimer >= spawnInterval) {
        spawnTimer -= spawnInterval;
        Enemy* e = nullptr;
        int type = std::rand() % 4;
        switch (type) {
        case 0: e = new Ogre(map, cellSize, speed);      break;
        case 1: e = new DarkElf(map, cellSize, speed);   break;
        case 2: e = new Harpy(map, cellSize, speed);     break;
        case 3: e = new Mercenary(map, cellSize, speed); break;
        }
        switch (type) {
        case 0: e->setColor(sf::Color(0, 100, 0));    break; // Ogro
        case 1: e->setColor(sf::Color(135, 206, 235));break; // Elfo Oscuro
        case 2: e->setColor(sf::Color(139, 69, 19));  break; // Harpía
        case 3: e->setColor(sf::Color(128, 128, 128));break; // Mercenario
        }
        enemies.push(e);
        ++spawnedCount;
    }
    for (int i = 0;i < enemies.size();++i) enemies.get(i)->update(dt);
    for (int i = 0; i < enemies.size();) {
        Enemy * e = enemies.get(i);
        if (!e->isAlive()) {
            // Suelta oro al morir
            // Nota: e->getGoldDrop() viene de Enemy
            player.addGold(e->getGoldDrop());
            enemies.removeAt(i);
        }
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

void WaveManager::resetAllEnemyPaths() {
    for (int i = 0; i < enemies.size(); ++i) {
        enemies.get(i)->resetPath();
    }
}