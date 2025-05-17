#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.hpp"
#include "Bullet.hpp"

class Tower {
public:
    Tower(int cost, float rangeCells, int damage, float reloadTime,
        float cellSize, int row, int col)
        : cost(cost), range(rangeCells), baseDamage(damage),
        reloadTime(reloadTime), reloadTimer(0.f),
        gridPos{ col,row }
    {
        shape.setRadius(cellSize * 0.4f);
        shape.setOrigin({ shape.getRadius(), shape.getRadius() });
        shape.setPosition({ col * cellSize + cellSize / 2, row * cellSize + cellSize / 2 });
    }
    virtual ~Tower() = default;

    // Nuevo update con lista de enemigos y balas
    void update(const std::vector<Enemy*>& enemies, float dt,
        std::vector<Bullet>& bullets) {
        // 1) validar target actual
        if (target) {
            if (!target->isAlive() || !inRange(target))
                target = nullptr;
        }
        // 2) buscar nuevo blanco si no hay target
        if (!target) {
            for (auto* e : enemies) {
                if (e->isAlive() && inRange(e)) {
                    target = e;
                    break;
                }
            }
        }
        // 3) recarga y disparo
        reloadTimer = std::max(0.f, reloadTimer - dt);
        if (target && target->isAlive() && reloadTimer <= 0.f) {
            shoot(bullets);
            reloadTimer = reloadTime;
        }
    }

    void draw(sf::RenderWindow& w) const { w.draw(shape); }
    int   getCost() const { return cost; }

protected:
    int cost;
    float range, baseDamage, reloadTime, reloadTimer;
    sf::CircleShape shape;
    sf::Vector2i gridPos;
    Enemy* target = nullptr;

    bool inRange(Enemy* e) const {
        auto gp = e->getGridPosition();
        int dx = std::abs(gridPos.x - gp.x),
            dy = std::abs(gridPos.y - gp.y);
        return std::sqrt(dx * dx + dy * dy) <= range;
    }

    void shoot(std::vector<Bullet>& bullets) {
        // calcular daño con resistencias
        float dmg = baseDamage;
        // detectar tipo vía color (o mejor vía dynamic_cast / enum)
        // aquí ejemplifico por distancia de rango:
        if (range >= 3) dmg *= (1.f - target->getArrowResistance());
        else if (range >= 2) dmg *= (1.f - target->getMagicResistance());
        else                 dmg *= (1.f - target->getArtilleryResistance());
        target->takeDamage(dmg);

        // crear efecto visual
        bullets.emplace_back(shape.getPosition(),
            target->getPosition());
        if (!target->isAlive()) target = nullptr;
    }
};

// Tres tipos, sólo cambian color y parámetros :contentReference[oaicite:2]{index=2}:contentReference[oaicite:3]{index=3}

class ArcherTower : public Tower {
public:
    ArcherTower(float cs, int r, int c)
        : Tower(50, 5, 10, 0.5f, cs, r, c)
    {
        shape.setFillColor({ 139,69,19 });
    }
};

class MageTower : public Tower {
public:
    MageTower(float cs, int r, int c)
        : Tower(100, 3, 20, 1.0f, cs, r, c)
    {
        shape.setFillColor({ 128,0,128 });
    }
};

class ArtilleryTower : public Tower {
public:
    ArtilleryTower(float cs, int r, int c)
        : Tower(150, 2, 40, 2.0f, cs, r, c)
    {
        shape.setFillColor(sf::Color::Black);
    }
};
