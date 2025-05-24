#include "GridMap.hpp"

// Implementa una cola FIFO utilizando un array circular para almacenar posiciones (sf::Vector2i).
// Evita el uso de estructuras gen�ricas de la STL.
class SimpleQueue {
public:
    // Construye una cola con capacidad 'capacity'
    SimpleQueue(int capacity)
        : cap(capacity)
        , head(0)
        , tail(0)
        , count(0)
    {
        data = new sf::Vector2i[cap];
    }
    // Libera la memoria interna
    ~SimpleQueue() {
        delete[] data;
    }
    // Encola un nuevo elemento al final si hay espacio
    void push(const sf::Vector2i& v) {
        if (count < cap) {
            data[tail] = v;
            tail = (tail + 1) % cap;  // avanzar �ndice circular
            ++count;
        }
    }
    // Devuelve el elemento al frente de la cola (sin extraerlo)
    sf::Vector2i front() const {
        return data[head];
    }
    // Elimina el elemento al frente, si la cola no est� vac�a
    void pop() {
        if (count > 0) {
            head = (head + 1) % cap;
            --count;
        }
    }
    // Indica si la cola est� vac�a
    bool empty() const {
        return count == 0;
    }

private:
    sf::Vector2i* data;  // almacenamiento circular
    int cap;             // capacidad m�xima
    int head;            // �ndice del primer elemento
    int tail;            // �ndice donde insertar el siguiente
    int count;           // n�mero de elementos actuales
};