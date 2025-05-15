#include "EnemyArray.hpp"
#include <cstdlib>

EnemyArray::EnemyArray(int initialCapacity)
    : capacity(initialCapacity), count(0)
{
    data = (Enemy**)std::malloc(sizeof(Enemy*) * capacity);
}

EnemyArray::~EnemyArray()
{
    clear(); std::free(data);
}

void EnemyArray::push(Enemy* e)
{
    if (count >= capacity) resize(); data[count++] = e;
}
Enemy* EnemyArray::get(int index) const { return data[index]; }
void EnemyArray::removeAt(int index)
{
    delete data[index]; for (int i = index; i < count - 1; ++i) data[i] = data[i + 1]; --count;
}
int EnemyArray::size() const { return count; }
void EnemyArray::clear() { for (int i = 0;i < count;++i) delete data[i]; count = 0; }
void EnemyArray::resize()
{
    int newCap = capacity * 2; Enemy** newData = (Enemy**)std::malloc(sizeof(Enemy*) * newCap); for (int i = 0;i < count;++i)newData[i] = data[i]; std::free(data); data = newData; capacity = newCap;
}