#pragma once
#include <cstddef>
#include <cassert>

// -----------------------------------
// SimpleVector: contenedor dinámico manual
// Implementa funcionalidades básicas similares a std::vector:
// - push_back()
// - operator[]
// - size()
// - clear()/resize()
// -----------------------------------

template<typename T>
class SimpleVector {
public:
    // Constructor: inicia vector vacío
    SimpleVector()
        : data(nullptr)
        , _size(0)
        , _capacity(0)
    {
    }

    // Destructor: libera memoria
    ~SimpleVector() {
        delete[] data;
    }

    // Añade un nuevo elemento al final
    void push_back(const T& value) {
        if (_size >= _capacity) {
            // Si no hay espacio, redimensionar (capacidad *2 o 1)
            size_t newCap = (_capacity == 0) ? 1 : _capacity * 2;
            reserve(newCap);
        }
        data[_size++] = value;
    }

    // Acceso a elementos (sin comprobación de rango)
    T& operator[](size_t index) {
        assert(index < _size);
        return data[index];
    }
    const T& operator[](size_t index) const {
        assert(index < _size);
        return data[index];
    }

    // Devuelve el número de elementos actuales
    size_t size() const {
        return _size;
    }

    // Cambia la capacidad para al menos 'newCap'
    void reserve(size_t newCap) {
        if (newCap <= _capacity) return;
        T* newData = new T[newCap];
        // Copiar elementos existentes
        for (size_t i = 0; i < _size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        _capacity = newCap;
    }

    // Limpia todos los elementos (size = 0) pero conserva capacidad
    void clear() {
        _size = 0;
    }

private:
    T* data;           // array dinámico de elementos
    size_t _size;      // número de elementos usados
    size_t _capacity;  // capacidad total del array
};