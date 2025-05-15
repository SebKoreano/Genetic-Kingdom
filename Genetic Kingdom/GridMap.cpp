#include "GridMap.hpp"

Node::Node(int row, int col, float size)
    : row(row), col(col)
{
    shape.setSize({ size - 1, size - 1 });
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
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            grid[r][c] = Node(r, c, cellSize);

    grid[start.y][start.x].shape.setFillColor(sf::Color::Green);
    grid[goal.y][goal.x].shape.setFillColor(sf::Color::Red);
}

void GridMap::draw(sf::RenderWindow& window)
{
    for (auto& row : grid)
        for (auto& node : row)
            window.draw(node.shape);
}

sf::Vector2i GridMap::getStartPosition() const { return start; }
sf::Vector2i GridMap::getGoalPosition() const { return goal; }
Node& GridMap::getNode(int row, int col) { return grid[row][col]; }

std::vector<Node*> GridMap::getNeighbors(Node& node)
{
    std::vector<Node*> neighbors;
    static const int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
    for (auto& d : dirs) {
        int nr = node.row + d[0], nc = node.col + d[1];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            Node& nbr = grid[nr][nc];
            if (nbr.walkable) neighbors.push_back(&nbr);
        }
    }
    return neighbors;
}
