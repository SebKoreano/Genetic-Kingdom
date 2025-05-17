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
      shape.setRadius(cellSize * 0.4f);  
      shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));  
      shape.setPosition(sf::Vector2f(col * cellSize + cellSize / 2.f, row * cellSize + cellSize / 2.f));  
  }  
  virtual ~Tower() = default;  

  void update(float dt) {  
      if (reloadTimer > 0.f) reloadTimer -= dt;  
  }  
  void draw(sf::RenderWindow& window) const { window.draw(shape); }  
  bool canAttack() const { return reloadTimer <= 0.f; }  
  void resetReload() { reloadTimer = reloadTime; }  

  int   getCost()   const { return cost; }  
  float getRange()  const { return range; }  
  int   getDamage() const { return damage; }  
  float getReload() const { return reloadTime; }  

protected:  
  int cost;  
  float range;  
  int damage;  
  float reloadTime;  
  float reloadTimer;  
  sf::CircleShape shape;  
};  

// Torres específicas 
class ArcherTower : public Tower {  
public:  
  ArcherTower(float cellSize, int row, int col)  
      : Tower(/*cost=*/ 50, /*range=*/5.f, /*damage=*/10, /*reloadTime=*/0.5f,  
          cellSize, row, col)  
  {  
      shape.setFillColor(sf::Color(139, 69, 19)); // Café claro
  }  
};  

class MageTower : public Tower {  
public:  
  MageTower(float cellSize, int row, int col)  
      : Tower(/*cost=*/100, /*range=*/3.f, /*damage=*/20, /*reloadTime=*/1.0f,  
          cellSize, row, col)  
  {  
      shape.setFillColor(sf::Color(128, 0, 128)); // Morado
  }  
};  

class ArtilleryTower : public Tower {  
public:  
  ArtilleryTower(float cellSize, int row, int col)  
      : Tower(/*cost=*/150, /*range=*/2.f, /*damage=*/40, /*reloadTime=*/2.0f,  
          cellSize, row, col)  
  {  
      shape.setFillColor(sf::Color::Black);        // Negro
  }  
};