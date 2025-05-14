#include "GridMap.hpp"

Node::Node(int row, int col, float size)
   : row(row), col(col)
{
   shape.setSize({ size - 1, size - 1 });  // margen visual
   shape.setPosition(sf::Vector2f(col * size, row * size)); 
   shape.setFillColor(sf::Color::Blue);
}

GridMap::GridMap(int rows, int cols, float cellSize)
   : rows(rows), cols(cols), cellSize(cellSize)
{
   createGrid();
}

void GridMap::createGrid()
{
   grid.resize(rows, std::vector<Node>(cols, Node(0, 0, cellSize)));

   for (int row = 0; row < rows; ++row)
   {
       for (int col = 0; col < cols; ++col)
       {
           grid[row][col] = Node(row, col, cellSize);
       }
   }

   grid[start.y][start.x].shape.setFillColor(sf::Color::Green);
   grid[goal.y][goal.x].shape.setFillColor(sf::Color::Red);

}

void GridMap::draw(sf::RenderWindow& window)
{
   for (const auto& row : grid)
       for (const auto& node : row)
           window.draw(node.shape);
}
