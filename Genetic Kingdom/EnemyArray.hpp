#pragma once
#include "Enemy.hpp"

class EnemyArray {
public:
    EnemyArray(int initCap = 10);
    ~EnemyArray();
    void push(Enemy* e);
    Enemy* get(int idx) const;
    void removeAt(int idx);
    int size() const;
    void clear();
private:
    Enemy** data;
    int cap, cnt;
    void resize();
};
