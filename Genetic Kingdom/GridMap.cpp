#include "GridMap.hpp"
#include "SimpleQueue.cpp"
#include <cassert>



Node::Node(int r, int c, float size)
    : row(r), col(c)
{
    shape.setSize({ size - 1.f, size - 1.f });
    shape.setPosition(sf::Vector2f(c * size, r * size));
    shape.setFillColor(sf::Color(34, 139, 34)); 
}

GridMap::GridMap(int rows_, int cols_, float cellSize_)
    : rows(rows_), cols(cols_), cellSize(cellSize_),
    start(0, 1), goal(cols_ - 1, rows_ - 2)
{
    createGrid();
}

void GridMap::createGrid() {
    grid.clear();
    grid.resize(rows, std::vector<Node>(cols, Node(0, 0, cellSize)));
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid[r][c] = Node(r, c, cellSize);
        }
    }
    grid[start.y][start.x].shape.setFillColor(sf::Color::Green);
    grid[goal.y][goal.x].shape.setFillColor(sf::Color::Red);
}

void GridMap::draw(sf::RenderWindow& window) const {
    for (const auto& row : grid) {
        for (const auto& node : row) {
            window.draw(node.shape);
        }
    }
}

Node& GridMap::getNode(int row, int col) {
    assert(row >= 0 && row < rows && col >= 0 && col < cols);
    return grid[row][col];
}

std::vector<Node*> GridMap::getNeighbors(const Node& node) const {
    std::vector<Node*> neighbors;
    static constexpr int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
    for (auto& d : dirs) {
        int nr = node.row + d[0];
        int nc = node.col + d[1];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            Node& nbr = const_cast<Node&>(grid[nr][nc]);
            if (nbr.walkable) neighbors.push_back(&nbr);
        }
    }
    return neighbors;
}

sf::Vector2i GridMap::getStartPosition() const { return start; }
sf::Vector2i GridMap::getGoalPosition()  const { return goal; }

void GridMap::toggleWalkable(int row, int col) {
    if ((row == start.y && col == start.x) || (row == goal.y && col == goal.x))
        return;
    grid[row][col].walkable = !grid[row][col].walkable;
}

bool GridMap::isPathAvailable() const {
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    SimpleQueue q(rows * cols);
    q.push(start);
    visited[start.y][start.x] = true;
    static constexpr int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

    while (!q.empty()) {
        sf::Vector2i p = q.front();
        q.pop();
        if (p == goal) return true;
        for (auto& d : dirs) {
            int nr = p.y + d[0];
            int nc = p.x + d[1];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !visited[nr][nc]) {
                if (grid[nr][nc].walkable) {
                    visited[nr][nc] = true;
                    q.push({ nc, nr });
                }
            }
        }
    }
    return false;
}

int GridMap::getRows() const { return rows; }
int GridMap::getCols() const { return cols; }
