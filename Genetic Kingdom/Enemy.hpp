#pragma once  
#include <SFML/Graphics.hpp>  
#include "GridMap.hpp"  
#include "NodeVector.h"  

class Enemy {  
public:
    Enemy(GridMap& map, float cellSize, float speed = 100.f);  
    void update(float dt);  
    void draw(sf::RenderWindow& window) const;  
    bool isAlive() const;  
    void resetPath();  
    void setColor(const sf::Color& color);  
    float speed;  
    float health = 100.f;  
    sf::Vector2i getGridPosition() const { return { currentCol, currentRow }; }  
    sf::Vector2f getPosition() const { return shape.getPosition(); }  
    float getArrowResistance()   const { return arrowResist; }  
    float getMagicResistance()   const { return magicResist; }  
    float getArtilleryResistance() const { return artilleryResist; }  
    void takeDamage(float d) {  
        health -= d;  
        if (health <= 0.f) alive = false;  
    }  
    int getGoldDrop() const { return goldDrop; }
private: 
    int goldDrop = 0;
    float arrowResist = 0.f,  
        magicResist = 0.f,  
        artilleryResist = 0.f;  
    GridMap& gridMap;  
    float cellSize;  
    NodeVector openList, closedList, path;  
    bool pathCalculated = false;  
    int pathIndex = 0;  
    int currentRow = 0, currentCol = 0;  
    bool alive = true;  
    sf::RectangleShape shape;  
    void calculatePath();  
    float heuristic(Node* a, Node* b) const;  
    Node* getLowestFCostNode();  
    bool isInList(const NodeVector&, Node*) const;  
    void reconstructPath(Node*);  
    friend class Ogre;       
    friend class DarkElf;  
    friend class Harpy;  
    friend class Mercenary;  
}; 