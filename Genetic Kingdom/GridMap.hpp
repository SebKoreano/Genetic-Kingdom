#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Node {
public:
    int row, col;                 // coordenadas fila y columna en la grilla
    bool walkable = true;         // indica si el nodo es transitable
    float gCost = 0, hCost = 0;   // costos para algoritmo A*
    Node* parent = nullptr;       // puntero al nodo padre en la ruta encontrada
    sf::RectangleShape shape;     // representaci�n gr�fica del nodo

    // Constructor: inicializa posici�n y tama�o del rect�ngulo
    Node(int r, int c, float size);
    // Costo total f = g + h
    float fCost() const { return gCost + hCost; }
};

class GridMap {
public:
    // rows: n�mero de filas
    // cols: n�mero de columnas
    // cellSize: tama�o en p�xeles de cada celda
    GridMap(int rows, int cols, float cellSize);

    // Dibuja todos los nodos en la ventana SFML
    void draw(sf::RenderWindow& window) const;

    // Accede a un nodo dado fila y columna
    Node& getNode(int row, int col);

    // Obtiene vecinos v�lidos (transitables) de un nodo (4 direcciones)
    std::vector<Node*> getNeighbors(const Node& node) const;

    // Obtiene la posici�n inicial (inicio de la ruta)
    sf::Vector2i getStartPosition() const;
    // Obtiene la posici�n meta (fin de la ruta)
    sf::Vector2i getGoalPosition() const;

    // Alterna si un nodo es transitable (walkable)
    void toggleWalkable(int row, int col);

    // Comprueba si existe un camino desde start hasta goal
    bool isPathAvailable() const;

    // Getters de dimensiones
    int getRows() const;
    int getCols() const;

private:
    int rows, cols;                      // dimensiones de la grilla
    float cellSize;                      // tama�o de cada celda en p�xeles
    std::vector<std::vector<Node>> grid; // matriz de nodos
    sf::Vector2i start;                  // posici�n de inicio en la grilla
    sf::Vector2i goal;                   // posici�n meta en la grilla

    // Inicializa la grilla y colorea start (verde) y goal (rojo)
    void createGrid();
};