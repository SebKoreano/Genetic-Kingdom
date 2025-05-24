#include "GridMap.hpp"
#include "SimpleQueue.cpp"
#include <cassert>

// Constructor de Node: ajusta tamaño y color verde predeterminado
Node::Node(int r, int c, float size)
    : row(r)
    , col(c)
{
    shape.setSize({ size - 1.f, size - 1.f });   // margen 1px para líneas visibles
    shape.setPosition(sf::Vector2f(c * size, r * size));
    shape.setFillColor(sf::Color(34, 139, 34));    // verde bosque
}

// Constructor de GridMap :
// Asigna filas, columnas, tamaño y define start/goal
GridMap::GridMap(int rows_, int cols_, float cellSize_)
    : rows(rows_)
    , cols(cols_)
    , cellSize(cellSize_)
    , start(0, 1)
    , goal(cols_ - 1, rows_ - 2)
{
    createGrid();
}

// Rellena 'grid' con nodos y colorea inicio/meta
void GridMap::createGrid() {
    grid.clear();
    grid.resize(rows, std::vector<Node>(cols, Node(0, 0, cellSize)));
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid[r][c] = Node(r, c, cellSize);
        }
    }
    // Start: verde claro, Goal: rojo
    grid[start.y][start.x].shape.setFillColor(sf::Color::Green);
    grid[goal.y][goal.x].shape.setFillColor(sf::Color::Red);
}

// Dibuja cada nodo en la ventana
void GridMap::draw(sf::RenderWindow& window) const {
    for (const auto& row : grid) {
        for (const auto& node : row) {
            window.draw(node.shape);
        }
    }
}

// Devuelve referencia al nodo 
Node& GridMap::getNode(int row, int col) {
    assert(row >= 0 && row < rows && col >= 0 && col < cols);
    return grid[row][col];
}

// Busca vecinos transitables en 4 direcciones
std::vector<Node*> GridMap::getNeighbors(const Node& node) const {
    std::vector<Node*> neighbors;
    static constexpr int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
    for (auto& d : dirs) {
        int nr = node.row + d[0];
        int nc = node.col + d[1];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            Node& nbr = const_cast<Node&>(grid[nr][nc]);
            if (nbr.walkable) {
                neighbors.push_back(&nbr);
            }
        }
    }
    return neighbors;
}

// Getter de posiciones start/goal
sf::Vector2i GridMap::getStartPosition() const { return start; }
sf::Vector2i GridMap::getGoalPosition()  const { return goal; }

// Alterna el estado walkable de un nodo, sin permitir cambiar start/goal
void GridMap::toggleWalkable(int row, int col) {
    if ((row == start.y && col == start.x) || (row == goal.y && col == goal.x))
        return;
    grid[row][col].walkable = !grid[row][col].walkable;
}

// Verificar conectividad start->goal
bool GridMap::isPathAvailable() const {
    // Matriz de marcados (visitados)
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    SimpleQueue q(rows * cols);
    q.push(start);
    visited[start.y][start.x] = true;
    static constexpr int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

    while (!q.empty()) {
        sf::Vector2i p = q.front();
        q.pop();
        if (p == goal) {
            return true;  // encontrado camino
        }
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
    return false;  // sin ruta válida
}

// Getters de rows y cols
int GridMap::getRows() const {  
    return rows;  
}  

int GridMap::getCols() const {  
    return cols;  
}
