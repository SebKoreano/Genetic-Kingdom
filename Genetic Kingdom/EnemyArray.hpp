#pragma once
#include "Enemy.hpp"

class EnemyArray {
public:
    EnemyArray(int initialCapacity = 10);
    ~EnemyArray();
    void push(Enemy* e);
    Enemy* get(int index) const;
    void removeAt(int index);
    int size() const;
    void clear();

private:
    Enemy** data;
    int capacity;
    int count;
    void resize();
};