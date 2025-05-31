#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Bullet {
    bool expired;               // Indica si la bala ya expiró
    sf::RectangleShape shape;
    float lifeTime;

public:
    // Constructor por defecto: bala expirada
    Bullet()
        : expired(true)
        , shape()
        , lifeTime(0.f)
    {
    }

    // Constructor principal: crea bala activa
    Bullet(const sf::Vector2f& startPos, const sf::Vector2f& targetPos)
        : expired(false)
        , shape()
        , lifeTime(0.1f)  // 100 ms visible
    {
        sf::Vector2f diff = targetPos - startPos;
        float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        shape.setSize({ distance, 4.f });
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin({ 0.f, 2.f });
        shape.setPosition(startPos);

        float angleInRadians = std::atan2(diff.y, diff.x);
        sf::Angle angle = sf::radians(angleInRadians);
        shape.setRotation(angle);
    }

    // Actualiza el tiempo de vida y marca expired si llega a cero
    void update(float dt) {
        if (expired) return;
        lifeTime -= dt;
        if (lifeTime <= 0.f) {
            expired = true;
        }
    }

    // Comprueba si la bala expiró
    bool isExpired() const {
        return expired;
    }

	// Devuelve la forma de la bala para dibujarla
    const sf::RectangleShape& getShape() const {
        return shape;
    }
};
