#include "NodeVector.h"
#include <iostream>

NodeVector::NodeVector() {
    capacity = 10;
    count = 0;
    data = new Node * [capacity];
}

NodeVector::~NodeVector() {
    delete[] data;
}

void NodeVector::resize() {
    capacity *= 2;
    Node** newData = new Node * [capacity];
    for (int i = 0; i < count; ++i)
        newData[i] = data[i];
    delete[] data;
    data = newData;
}

void NodeVector::push_back(Node* node) {
    if (count >= capacity)
        resize();
    data[count++] = node;
}

Node* NodeVector::get(int index) const {
    if (index >= 0 && index < count)
        return data[index];
    return nullptr;
}

void NodeVector::removeAt(int index) {
    if (index >= 0 && index < count) {
        for (int i = index; i < count - 1; ++i)
            data[i] = data[i + 1];
        --count;
    }
}

int NodeVector::size() const {
    return count;
}

void NodeVector::clear() {
    count = 0;
}
