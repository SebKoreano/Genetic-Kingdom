#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Node {
public:
    sf::RectangleShape shape;
    int row, col;
    bool walkable = true;
    float gCost = 0;
    float hCost = 0;
    Node* parent = nullptr;

    Node(int row, int col, float size);
    float fCost() const { return gCost + hCost; }
};

class GridMap {
public:
    GridMap(int rows, int cols, float cellSize);
    void draw(sf::RenderWindow& window) const;
    sf::Vector2i getStartPosition() const;
    sf::Vector2i getGoalPosition() const;
    Node& getNode(int row, int col);
    std::vector<Node*> getNeighbors(Node& node) const;
    void toggleWalkable(int row, int col);
    bool isPathAvailable() const;

private:
    int rows, cols;
    float cellSize;
    std::vector<std::vector<Node>> grid;
    void createGrid();
    sf::Vector2i start = { 0,1 };
    sf::Vector2i goal = { 19,13 };
};