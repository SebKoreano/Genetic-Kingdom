#pragma once  
#include <SFML/Graphics/RectangleShape.hpp>  

class Bullet {  
private:  
   sf::RectangleShape shape;  
   float lifeTime;  
public:  
   Bullet(sf::Vector2f startPos, sf::Vector2f endPos);  
   void update(float dt);  
   bool isExpired() const;  
   const sf::RectangleShape& getShape() const;  
};