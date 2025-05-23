#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.hpp"
#include "Bullet.hpp"

class Tower {
public:
    Tower(int cost, float rangeCells, float damage, float reloadTime,
        float cellSize, int row, int col)
        : baseCost(cost)
        , cost(cost)
        , range(rangeCells)
        , baseDamage(damage)
        , currentDamage(damage)
        , reloadTime(reloadTime)
        , cellSize(cellSize)
        , level(1)
        , gridPos{ col,row }
    {
        // base shape
        shape.setRadius(cellSize * 0.4f);
        shape.setOrigin({ shape.getRadius(), shape.getRadius() });
        shape.setPosition(sf::Vector2f(col * cellSize + cellSize / 2.f, row * cellSize + cellSize / 2.f));
    }
    virtual ~Tower() = default;

    // Update: acquire target and shoot
    void update(const std::vector<Enemy*>& enemies, float dt,
        std::vector<Bullet>& bullets) {
        // maintain target
        if (target) {
            if (!target->isAlive() || !inRange(target)) target = nullptr;
        }
        // find new target
        if (!target) {
            for (auto* e : enemies) {
                if (e->isAlive() && inRange(e)) {
                    target = e;
                    break;
                }
            }
        }
        // reload
        reloadTimer = std::max(0.f, reloadTimer - dt);
        if (target && reloadTimer <= 0.f) {
            shoot(bullets);
            reloadTimer = reloadTime;
        }
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
        // draw upgrade overlays inside
        for (auto& overlay : overlays) window.draw(overlay);
    }

    int getCost() const { return cost; }
    sf::Vector2i getGridPosition() const { return gridPos; }
    int getUpgradeCost() const {
        return static_cast<int>(baseCost * (1.f + 0.25f * level));
    }
    bool canUpgrade() const { return level < 3; }

    void upgrade() {
        if (!canUpgrade()) return;
        // increase cost
        cost = getUpgradeCost();
        // increase damage 90%
        currentDamage *= 1.90f;
        // reduce reload time 20%
        reloadTime *= 0.80f;
        // graphical overlay
        float newRadius = shape.getRadius() * 0.75f;
        sf::CircleShape ovr(newRadius);
        ovr.setOrigin({ newRadius, newRadius });
        ovr.setPosition(shape.getPosition());
        sf::Color baseColor = shape.getFillColor();
        if (baseColor == sf::Color::Black) {
            // artillery: lighten overlay
            ovr.setFillColor(sf::Color(
                std::min(255, baseColor.r + 50),
                std::min(255, baseColor.g + 50),
                std::min(255, baseColor.b + 50)
            ));
        }
        else {
            // darken overlay
            ovr.setFillColor(sf::Color(
                baseColor.r * 0.7f,
                baseColor.g * 0.7f,
                baseColor.b * 0.7f
            ));
        }
        overlays.push_back(ovr);
        // increment level
        ++level;
    }

protected:
    int baseCost;
    int cost;
    float range;
    float baseDamage;
    float currentDamage;
    float reloadTime;
    float reloadTimer = 0.f;
    float cellSize;
    sf::CircleShape shape;
    sf::Vector2i gridPos;
    Enemy* target = nullptr;
    int level;
    std::vector<sf::CircleShape> overlays;

    bool inRange(Enemy* e) const {
        auto gp = e->getGridPosition();
        int dx = std::abs(gridPos.x - gp.x);
        int dy = std::abs(gridPos.y - gp.y);
        return std::sqrt(dx * dx + dy * dy) <= range;
    }

    void shoot(std::vector<Bullet>& bullets) {
        // apply damage with resistances
        float dmg = currentDamage;
        if (range >= 3) dmg *= (1.f - target->getArrowResistance());
        else if (range >= 2) dmg *= (1.f - target->getMagicResistance());
        else                 dmg *= (1.f - target->getArtilleryResistance());
        target->takeDamage(dmg);
        // create bullet effect
        bullets.emplace_back(shape.getPosition(), target->getPosition());
        if (!target->isAlive()) target = nullptr;
    }
};

// Specific towers
class ArcherTower : public Tower {
public:
    ArcherTower(float cs, int r, int c)
        : Tower(50, 3, 10, 0.5f, cs, r, c)
    {
        shape.setFillColor({ 139, 69, 19 });
    }
};

class MageTower : public Tower {
public:
    MageTower(float cs, int r, int c)
        : Tower(100, 2, 20, 1.0f, cs, r, c)
    {
        shape.setFillColor({ 128, 0, 128 });
    }
};

class ArtilleryTower : public Tower {
public:
    ArtilleryTower(float cs, int r, int c)
        : Tower(150, 1, 40, 2.0f, cs, r, c)
    {
        shape.setFillColor(sf::Color::Black);
    }
};
