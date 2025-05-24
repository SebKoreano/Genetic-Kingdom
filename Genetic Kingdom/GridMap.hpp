#pragma once
#include <SFML/Graphics.hpp>
#include "SimpleVector.hpp"

class Node {
public:
    Node()
        : row(0), col(0), walkable(true), gCost(0), hCost(0), parent(nullptr)
    {
    }
    int row, col;                 // coordenadas fila y columna en la grilla
    bool walkable = true;         // indica si el nodo es transitable
    float gCost = 0, hCost = 0;   // costos para algoritmo A*
    Node* parent = nullptr;       // puntero al nodo padre en la ruta encontrada
    sf::RectangleShape shape;     // representación gráfica del nodo

    // Constructor: inicializa posición y tamaño del rectángulo
    Node(int r, int c, float size);
    // Costo total f = g + h
    float fCost() const { return gCost + hCost; }
};

class GridMap {
public:
    // rows: número de filas
    // cols: número de columnas
    // cellSize: tamaño en píxeles de cada celda
    GridMap(int rows_, int cols_, float cellSize_);
    ~GridMap();

    // Dibuja todos los nodos en la ventana SFML
    void draw(sf::RenderWindow& window) const;

    // Accede a un nodo dado fila y columna
    Node& getNode(int row, int col);

    // Obtiene vecinos válidos (transitables) de un nodo (4 direcciones)
    SimpleVector<Node*> getNeighbors(const Node& node) const;

    // Obtiene la posición inicial (inicio de la ruta)
    sf::Vector2i getStartPosition() const;
    // Obtiene la posición meta (fin de la ruta)
    sf::Vector2i getGoalPosition() const;

    // Alterna si un nodo es transitable (walkable)
    void toggleWalkable(int row, int col);

    // Comprueba si existe un camino desde start hasta goal
    bool isPathAvailable() const;

    // Getters de dimensiones
    int getRows() const;
    int getCols() const;

private:
    int rows, cols;         // dimensiones de la grilla
    float cellSize;         // tamaño de cada celda en píxeles
    Node* grid;             // array lineal de nodos
    sf::Vector2i start;     // posición de inicio en la grilla
    sf::Vector2i goal;      // posición meta en la grilla

    // Inicializa la grilla y colorea start (verde) y goal (rojo)
    void createGrid();
};