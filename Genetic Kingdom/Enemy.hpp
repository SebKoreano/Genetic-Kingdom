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

private:
    GridMap& gridMap;
    float cellSize;
    float speed;
    NodeVector openList, closedList, path;
    bool pathCalculated = false;
    int pathIndex = 0;
    int currentRow = 0, currentCol = 0;
    bool alive = true;
    sf::RectangleShape shape;

    void calculatePath();
    float heuristic(Node* a, Node* b) const;
    Node* getLowestFCostNode();
    bool isInList(const NodeVector& list, Node* node) const;
    void reconstructPath(Node* endNode);
};