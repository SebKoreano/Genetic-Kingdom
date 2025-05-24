#include "GridMap.hpp"

// Cola circular simple para evitar estructuras genéricas
class SimpleQueue {
public:
    SimpleQueue(int capacity)
        : cap(capacity), head(0), tail(0), count(0)
    {
        data = new sf::Vector2i[cap];
    }
    ~SimpleQueue() {
        delete[] data;
    }
    void push(const sf::Vector2i& v) {
        if (count < cap) {
            data[tail] = v;
            tail = (tail + 1) % cap;
            ++count;
        }
    }
    sf::Vector2i front() const {
        return data[head];
    }
    void pop() {
        if (count > 0) {
            head = (head + 1) % cap;
            --count;
        }
    }
    bool empty() const {
        return count == 0;
    }
private:
    sf::Vector2i* data;
    int cap;
    int head;
    int tail;
    int count;
};