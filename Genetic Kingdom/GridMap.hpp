#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Node {
public:
    int row, col;
    bool walkable = true;
    float gCost = 0, hCost = 0;
    Node* parent = nullptr;
    sf::RectangleShape shape;

    Node(int r, int c, float size);
    float fCost() const { return gCost + hCost; }
};

class GridMap {
public:
    GridMap(int rows, int cols, float cellSize);
    void draw(sf::RenderWindow& window) const;
    Node& getNode(int row, int col);
    std::vector<Node*> getNeighbors(const Node& node) const;
    sf::Vector2i getStartPosition() const;
    sf::Vector2i getGoalPosition() const;
    void toggleWalkable(int row, int col);
    bool isPathAvailable() const;
    int getRows() const;
    int getCols() const;

private:
    int rows, cols;
    float cellSize;
    std::vector<std::vector<Node>> grid;
    sf::Vector2i start;
    sf::Vector2i goal;
    void createGrid();
};