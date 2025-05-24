#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "SimpleVector.hpp"

class Tower {
public:
    Tower(int cost, float rangeCells, float damage, float reloadTime,
        float cellSize, int row, int col)
        : baseCost(cost), cost(cost), range(rangeCells),
        baseDamage(damage), currentDamage(damage),
        reloadTime(reloadTime), cellSize(cellSize), level(1),
        gridPos{ col,row }
    {
        shape.setRadius(cellSize * 0.4f);
        shape.setOrigin({ shape.getRadius(), shape.getRadius() });
        shape.setPosition({ col * cellSize + cellSize / 2.f,
                            row * cellSize + cellSize / 2.f });
    }
    virtual ~Tower() = default;

    // Actualiza torre: encuentra objetivo y dispara
    void update(const SimpleVector<Enemy*>& enemies, float dt,
        SimpleVector<Bullet>& bullets) {
        if (target) {
            if (!target->isAlive() || !inRange(target)) target = nullptr;
        }
        if (!target) {
            for (size_t i = 0;i < enemies.size();++i) {
                Enemy* e = enemies[i];
                if (e->isAlive() && inRange(e)) { target = e; break; }
            }
        }
        reloadTimer = std::max(0.f, reloadTimer - dt);
        if (target && reloadTimer <= 0.f) {
            // sustituye emplace_back por push_back
            float dmg = currentDamage;
            if (range >= 3) dmg *= (1 - target->getArrowResistance());
            else if (range >= 2) dmg *= (1 - target->getMagicResistance());
            else dmg *= (1 - target->getArtilleryResistance());
            target->takeDamage(dmg);
            bullets.push_back(Bullet(shape.getPosition(), target->getPosition()));
            if (!target->isAlive()) target = nullptr;
            reloadTimer = reloadTime;
        }
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
        for (size_t i = 0;i < overlays.size();++i)
            window.draw(overlays[i]);
    }

    int getCost() const { return cost; }
    sf::Vector2i getGridPosition() const { return gridPos; }
    int getUpgradeCost() const { return static_cast<int>(baseCost * (1 + 0.25f * level)); }
    bool canUpgrade() const { return level < 3; }

    void upgrade() {
        if (!canUpgrade()) return;
        cost = getUpgradeCost();
        currentDamage *= 1.9f;
        reloadTime *= 0.8f;
        float r = shape.getRadius() * 0.75f;
        sf::CircleShape ovr(r);
        ovr.setOrigin({ r,r });
        ovr.setPosition(shape.getPosition());
        auto c = shape.getFillColor();
        if (c == sf::Color::Black)
            ovr.setFillColor(sf::Color(
                std::min(255, c.r + 50), std::min(255, c.g + 50), std::min(255, c.b + 50)
            ));
        else
            ovr.setFillColor(sf::Color(c.r * 0.7f, c.g * 0.7f, c.b * 0.7f));
        overlays.push_back(ovr);
        ++level;
    }

protected:
    int baseCost, cost;
    float range, baseDamage, currentDamage;
    float reloadTime, reloadTimer = 0.f;
    float cellSize;
    sf::CircleShape shape;
    sf::Vector2i gridPos;
    Enemy* target = nullptr;
    int level;
    SimpleVector<sf::CircleShape> overlays;

    bool inRange(Enemy* e) const {
        auto gp = e->getGridPosition();
        int dx = std::abs(gridPos.x - gp.x), dy = std::abs(gridPos.y - gp.y);
        return std::sqrt(dx * dx + dy * dy) <= range;
    }
};

class ArcherTower :public Tower {
public:ArcherTower(float cs, int r, int c)
    :Tower(50, 3, 10, 0.5f, cs, r, c) {
    shape.setFillColor({ 139,69,19 });
}
};
class MageTower :public Tower {
public:MageTower(float cs, int r, int c)
    :Tower(100, 2, 20, 1.0f, cs, r, c) {
    shape.setFillColor({ 128,0,128 });
}
};
class ArtilleryTower :public Tower {
public:ArtilleryTower(float cs, int r, int c)
    :Tower(150, 1, 40, 2.0f, cs, r, c) {
    shape.setFillColor(sf::Color::Black);
}
};