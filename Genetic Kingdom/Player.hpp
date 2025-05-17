#pragma once

// Clase para gestionar recursos del jugador
class Player {
public:
    Player(int startGold = 400, int startLives = 20)
        : gold(startGold)
        , lives(startLives)
    {
    }

    // Intenta gastar oro; devuelve true si fue posible
    bool spendGold(int amount) {
        if (gold >= amount) {
            gold -= amount;
            return true;
        }
        return false;
    }

    // Aumenta el oro del jugador
    void addGold(int amount) {
        gold += amount;
    }

    // Quita vidas al jugador
    void loseLife(int amount = 1) {
        lives -= amount;
        if (lives < 0) lives = 0;
    }

    int getGold() const { return gold; }
    int getLives() const { return lives; }

private:
    int gold;
    int lives;
};