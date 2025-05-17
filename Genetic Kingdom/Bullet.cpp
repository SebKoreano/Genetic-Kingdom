#include <cmath>  
#include "Bullet.hpp"  

Bullet::Bullet(sf::Vector2f startPos, sf::Vector2f endPos) {  
   sf::Vector2f diff = endPos - startPos;  
   float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);  
   shape.setSize(sf::Vector2f(distance, 4.f));  
   shape.setFillColor(sf::Color::Yellow);  
   shape.setOrigin(sf::Vector2f(0.f, 2.f));  
   shape.setPosition(startPos);  
   float angleInRadians = std::atan2(diff.y, diff.x);  
   sf::Angle angle = sf::radians(angleInRadians);  
   shape.setRotation(angle);
   lifeTime = 0.1f;  
}  

void Bullet::update(float dt) {  
   lifeTime -= dt;  
}  

bool Bullet::isExpired() const {  
   return lifeTime <= 0.f;  
}  

const sf::RectangleShape& Bullet::getShape() const {  
   return shape;  
}