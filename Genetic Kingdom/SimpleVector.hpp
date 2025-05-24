#pragma once
#include <cstddef>
#include <cassert>

// -----------------------------------
// SimpleVector: contenedor dinámico manual
// Implementa funcionalidades básicas similares a std::vector:
// - push_back(), pop_back(), removeAt()
// - operator[]
// - size(), clear(), reserve()
// -----------------------------------

template<typename T>
class SimpleVector {
public:
    SimpleVector()
        : data(nullptr), _size(0), _capacity(0) {
    }
    ~SimpleVector() { delete[] data; }

    void push_back(const T& value) {
        if (_size >= _capacity) {
            size_t newCap = (_capacity == 0) ? 1 : _capacity * 2;
            reserve(newCap);
        }
        data[_size++] = value;
    }

    void pop_back() {
        assert(_size > 0);
        --_size;
    }
    void removeAt(size_t index) {
        assert(index < _size);
        for (size_t i = index; i + 1 < _size; ++i)
            data[i] = data[i + 1];
        --_size;
    }

    T& operator[](size_t index) {
        assert(index < _size);
        return data[index];
    }
    const T& operator[](size_t index) const {
        assert(index < _size);
        return data[index];
    }

    size_t size() const { return _size; }

    void reserve(size_t newCap) {
        if (newCap <= _capacity) return;
        T* newData = new T[newCap];
        for (size_t i = 0; i < _size; ++i) newData[i] = data[i];
        delete[] data;
        data = newData;
        _capacity = newCap;
    }

    void clear() { _size = 0; }

private:
    T* data;
    size_t _size;
    size_t _capacity;
};
