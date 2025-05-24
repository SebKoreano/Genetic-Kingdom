#include "WaveManager.hpp"
#include "Ogre.hpp"
#include "DarkElf.hpp"
#include "Harpy.hpp"
#include "Mercenary.hpp"
#include <algorithm>
#include <numeric>
#include <ctime>

WaveManager::WaveManager(GridMap& m, float cs, float sp,
    int mi, int ma, const sf::Font& font)
    : map(m)
    , cellSize(cs)
    , speed(sp)
    , minEnemies(mi)
    , maxEnemies(ma)
    , waveNumber(1)
    , enemies(10)
    , waveText(font) 
{
    waveText.setCharacterSize(24);
    waveText.setFillColor(sf::Color::White);
    waveText.setString("");
    waveText.setPosition({ 5.f,map.getStartPosition().y * cellSize + (map.getGoalPosition().y + 1) * cellSize + 5.f });

    std::srand(unsigned(std::time(nullptr)));
    spawnWave();
}


void WaveManager::spawnWave() {
    enemies.clear();
    tracked.clear();
    for (int t = 0;t < 4;++t) fitness[t].clear();

    int cnt[4];
    for (int t = 0;t < 4;++t)
        cnt[t] = std::rand() % (maxEnemies - minEnemies + 1) + minEnemies;

    // 1ª oleada: genes random. Luego: evoluciona y redimensiona.
    for (int t = 0;t < 4;++t) {
        if (waveNumber == 1) {
            genes[t].resize(cnt[t]);
            for (int i = 0;i < cnt[t];++i) {
                Genes& g = genes[t][i];
                switch (t) {
                case 0: // Ogre
                    g.speed = randF(30, 50); g.health = randF(120, 160);
                    g.arrowResist = randF(0, 0.4f); g.magicResist = randF(0, 0.3f);
                    g.artilleryResist = randF(0.1f, 0.5f);
                    break;
                case 1: // DarkElf
                    g.speed = randF(60, 80); g.health = randF(70, 110);
                    g.arrowResist = randF(0.1f, 0.5f); g.magicResist = randF(0.5f, 1);
                    g.artilleryResist = randF(0.1f, 0.5f);
                    break;
                case 2: // Harpy
                    g.speed = randF(40, 60); g.health = randF(80, 120);
                    g.arrowResist = randF(0, 0.2f); g.magicResist = randF(0, 0.2f);
                    g.artilleryResist = randF(0.3f, 0.7f);
                    break;
                default: // Mercenary
                    g.speed = randF(60, 80); g.health = randF(90, 130);
                    g.arrowResist = randF(0.5f, 1); g.magicResist = randF(0.1f, 0.5f);
                    g.artilleryResist = randF(0.5f, 1);
                }
            }
        }
        else {
            evolve(t);
            genes[t].resize(cnt[t]);
        }
    }

    // Crear y trackear
    for (int t = 0;t < 4;++t) {
        for (int i = 0;i < genes[t].size();++i) {
            Enemy* e = makeEnemy(t, i);
            enemies.push(e);
            tracked.push_back({ e,t,i,0.f });
        }
    }
}

Enemy* WaveManager::makeEnemy(int type, int idx) {
    const Genes& g = genes[type][idx];
    if (type == 0) return new Ogre(map, cellSize, g);
    if (type == 1) return new DarkElf(map, cellSize, g);
    if (type == 2) return new Harpy(map, cellSize, g);
    return new Mercenary(map, cellSize, g);
}

void WaveManager::update(float dt, Player& player) {
    for (size_t i = 0; i < tracked.size();) {
        // Actualizar el tiempo de vida y el movimiento
        tracked[i].t += dt;
        tracked[i].e->update(dt);
        // Si el enemigo murió o alcanzó meta (alive=false)
        if (!tracked[i].e->isAlive()) {
            int ty = tracked[i].type;
            // Guardar fitness
            fitness[ty].push_back(tracked[i].t);
            // Recompensas
            if (tracked[i].e->hasReachedGoal()) player.loseLife();
            else player.addGold(tracked[i].e->getGoldDrop());
            // Eliminar de la lista de enemigos activos
            for (int k = 0; k < enemies.size(); ++k) {
                if (enemies.get(k) == tracked[i].e) {
                    enemies.removeAt(k);
                    break;
                }
            }
            // Quitar del seguimiento
            tracked.erase(tracked.begin() + i);
        }
        else {
            ++i;
        }
    }

    // Si no quedan enemigos vivos ni en seguimiento, nueva oleada
    if (tracked.empty()) {
        ++waveNumber;
        spawnWave();
    }
}


void WaveManager::draw(sf::RenderWindow& w) {
    map.draw(w);
    for (int i = 0; i < enemies.size(); ++i)
        enemies.get(i)->draw(w);
    waveText.setString("Oleada: " + std::to_string(waveNumber));
    w.draw(waveText);
}

void WaveManager::handleClick(int x, int y) {
    // (igual que antes)
}

void WaveManager::resetAllEnemyPaths() {
    for (int i = 0;i < enemies.size();++i)
        enemies.get(i)->resetPath();
}

void WaveManager::evolve(int type) {
    auto& G = genes[type]; auto& F = fitness[type];
    size_t N = G.size();
    if (F.size() != N || N < 2) return;

    // identif. top 2
    size_t m1 = 0, m2 = 1;
    for (size_t i = 1;i < N;++i) {
        if (F[i] > F[m1]) { m2 = m1; m1 = i; }
    }
    if (m2 == m1) m2 = (m1 + 1) % N;

    Genes p1 = G[m1], p2 = G[m2];
    std::vector<Genes> nxt(N);
    for (size_t i = 0;i < N;++i) {
        // promedio + mutación ±10%
        nxt[i].speed = (p1.speed + p2.speed) / 2 * randF(0.9f, 1.1f);
        nxt[i].health = (p1.health + p2.health) / 2 * randF(0.9f, 1.1f);
        nxt[i].arrowResist = (p1.arrowResist + p2.arrowResist) / 2 * randF(0.9f, 1.1f);
        nxt[i].magicResist = (p1.magicResist + p2.magicResist) / 2 * randF(0.9f, 1.1f);
        nxt[i].artilleryResist = (p1.artilleryResist + p2.artilleryResist) / 2 * randF(0.9f, 1.1f);
    }
    G.swap(nxt);
}
