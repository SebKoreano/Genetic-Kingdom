#pragma once
#include <SFML/Graphics.hpp>
#include "GridMap.hpp"
#include "EnemyArray.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

struct Genes {
    float speed;
    float health;
    float arrowResist;
    float magicResist;
    float artilleryResist;
};

class WaveManager {
public:
    // Devuelve una copia de la lista de enemigos actuales para iterar sobre ellos
    std::vector<Enemy*> getEnemyList() const {
        std::vector<Enemy*> list;
        for (int i = 0; i < enemies.size(); ++i)
            list.push_back(enemies.get(i));
        return list;
    }
    WaveManager(GridMap& map, float cellSize, float speed,
        int minEnemies, int maxEnemies,
        const sf::Font& font);

    void handleClick(int x, int y);
    void update(float dt, Player& player);
    void draw(sf::RenderWindow& window);
    void resetAllEnemyPaths();

private:
    GridMap& map;
    float cellSize, speed;
    int minEnemies, maxEnemies, waveNumber;
    EnemyArray enemies;
    sf::Text waveText;

    // Para cada tipo: 0=Ogre,1=DarkElf,2=Harpy,3=Mercenary
    std::vector<Genes> genes[4];
    std::vector<float> fitness[4];

    struct Tracked { Enemy* e; int type, idx; float t; };
    std::vector<Tracked> tracked;

    static float randF(float a, float b) {
        return a + static_cast<float>(std::rand()) / RAND_MAX * (b - a);
    }

    void spawnWave();
    Enemy* makeEnemy(int type, int idx);
    void evolve(int type);
};