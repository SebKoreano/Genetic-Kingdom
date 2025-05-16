#pragma once
#include <SFML/Graphics.hpp>

// Clase base para torres
class Tower {
public:
    Tower(int cost, float range, int damage, float reloadTime, float cellSize,
        int row, int col)
        : cost(cost)
        , range(range)
        , damage(damage)
        , reloadTime(reloadTime)
        , reloadTimer(0.f)
    {
        // Configurar forma circular para la torre
        shape.setRadius(cellSize * 0.4f);
        shape.setOrigin(shape.getRadius(), shape.getRadius());
        shape.setPosition(col * cellSize + cellSize / 2.f,
            row * cellSize + cellSize / 2.f);
    }
    virtual ~Tower() = default;

    // Actualiza el temporizador de recarga
    void update(float dt) {
        if (reloadTimer > 0.f)
            reloadTimer -= dt;
    }

    // Dibuja la torre en pantalla
    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }

    // Verifica si la torre puede atacar
    bool canAttack() const {
        return reloadTimer <= 0.f;
    }

    // Reinicia el temporizador tras un ataque
    void resetReload() {
        reloadTimer = reloadTime;
    }

    // Getters
    int   getCost()     const { return cost; }
    float getRange()    const { return range; }
    int   getDamage()   const { return damage; }
    float getReload()   const { return reloadTime; }

protected:
    int cost;             // Costo en oro
    float range;          // Alcance en unidades de celda
    int damage;           // Daño por ataque
    float reloadTime;     // Tiempo de recarga entre ataques (s)
    float reloadTimer;    // Temporizador actual
    sf::CircleShape shape; // Representación gráfica
};