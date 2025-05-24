#include "GridMap.hpp"
#include "SimpleQueue.hpp"
#include "SimpleVector.hpp"
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
    : rows(rows_), cols(cols_), cellSize(cellSize_),
    start(0, 1), goal(cols_ - 1, rows_ - 2)
{
    // Reserva inmediata:
    grid = new Node[rows * cols];
    createGrid();
}

GridMap::~GridMap() {
    delete[] grid;
}

// Rellena 'grid' con nodos y colorea inicio/meta
void GridMap::createGrid() {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int idx = r * cols + c;
            grid[idx] = Node(r, c, cellSize);
        }
    }
    // Colores de start/goal
    grid[start.y * cols + start.x].shape.setFillColor(sf::Color::Green);
    grid[goal.y * cols + goal.x].shape.setFillColor(sf::Color::Red);
}

// Dibuja cada nodo en la ventana
void GridMap::draw(sf::RenderWindow& window) const {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int idx = r * cols + c;
            window.draw(grid[idx].shape);
        }
    }
}


// Devuelve referencia al nodo (fila, columna) usando el índice lineal
Node& GridMap::getNode(int row, int col) {
    assert(row >= 0 && row < rows && col >= 0 && col < cols);
    int idx = row * cols + col;
    return grid[idx];
}

// Obtiene vecinos transitables usando aritmética de punteros
SimpleVector<Node*> GridMap::getNeighbors(const Node& node) const {
    SimpleVector<Node*> neighbors;
    static constexpr int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
    for (auto& d : dirs) {
        int nr = node.row + d[0];
        int nc = node.col + d[1];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            int idx = nr * cols + nc;
            Node& nbr = grid[idx];
            if (nbr.walkable)
                neighbors.push_back(&nbr);
        }
    }
    return neighbors;
}

// Getter de posiciones start/goal
sf::Vector2i GridMap::getStartPosition() const { return start; }
sf::Vector2i GridMap::getGoalPosition()  const { return goal; }

// Alterna walkable usando el índice lineal
void GridMap::toggleWalkable(int row, int col) {
    // No tocar start/goal
    if ((row == start.y && col == start.x) || (row == goal.y && col == goal.x))
        return;
    int idx = row * cols + col;
    grid[idx].walkable = !grid[idx].walkable;
}

// Verificar conectividad start->goal
bool GridMap::isPathAvailable() const {
    // Array dinámico de visitados
    bool* visited = new bool[rows * cols];
    for (int i = 0; i < rows * cols; ++i) visited[i] = false;

    SimpleQueue q(rows * cols);
    q.push(start);
    visited[start.y * cols + start.x] = true;

    static constexpr int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
    while (!q.empty()) {
        sf::Vector2i p = q.front(); q.pop();
        if (p == goal) {
            delete[] visited;
            return true;
        }
        for (auto& d : dirs) {
            int nr = p.y + d[0];
            int nc = p.x + d[1];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                int idx = nr * cols + nc;
                if (!visited[idx] && grid[idx].walkable) {
                    visited[idx] = true;
                    q.push({ nc, nr });
                }
            }
        }
    }
    delete[] visited;
    return false;
}

// Getters de rows y cols
int GridMap::getRows() const {  
    return rows;  
}  

int GridMap::getCols() const {  
    return cols;  
}
