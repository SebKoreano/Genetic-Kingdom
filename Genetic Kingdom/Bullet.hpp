#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
    sf::RectangleShape shape;
    float lifeTime;
public:
    Bullet(const sf::Vector2f& startPos, const sf::Vector2f& targetPos) {
        sf::Vector2f diff = targetPos - startPos;
        float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        shape.setSize({ distance, 4.f });
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin({ 0.f, 2.f });
        shape.setPosition(startPos);
        float angleInRadians = std::atan2(diff.y, diff.x);
        sf::Angle angle = sf::radians(angleInRadians);
        shape.setRotation(angle);
        lifeTime = 0.1f; // 100 ms visible
    }
    void update(float dt) { lifeTime -= dt; }
    bool isExpired() const { return lifeTime <= 0.f; }
    const sf::RectangleShape& getShape() const { return shape; }
};
