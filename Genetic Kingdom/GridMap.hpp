#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Node {
public:
    sf::RectangleShape shape;
    int row, col;

    Node(int row, int col, float size);
};

class GridMap {
public:
    GridMap(int rows, int cols, float cellSize);
    void draw(sf::RenderWindow& window);
    sf::Vector2i getStartPosition() const;
    sf::Vector2i getGoalPosition() const;


private:
    int rows, cols;
    float cellSize;
    std::vector<std::vector<Node>> grid;
    void createGrid();
    sf::Vector2i start = { 0, 1 }; 
    sf::Vector2i goal = { 19, 13 }; 

};
