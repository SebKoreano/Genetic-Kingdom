#pragma once
#ifndef NODEVECTOR_H
#define NODEVECTOR_H
#include "./GridMap.hpp"

class NodeVector {
private:
    Node** data;
    int capacity;
    int count;

    void resize();

public:
    NodeVector();
    ~NodeVector();

    void push_back(Node* node);
    Node* get(int index) const;
    void removeAt(int index);
    int size() const;
    void clear();
};

#endif
