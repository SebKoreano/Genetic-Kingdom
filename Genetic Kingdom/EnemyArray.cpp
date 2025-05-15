#include "EnemyArray.hpp"
#include <cstdlib>

EnemyArray::EnemyArray(int initCap)
    : cap(initCap), cnt(0)
{
    data = (Enemy**)std::malloc(sizeof(Enemy*) * cap);
}
EnemyArray::~EnemyArray() { clear(); std::free(data); }
void EnemyArray::push(Enemy* e) { if (cnt >= cap)resize(); data[cnt++] = e; }
Enemy* EnemyArray::get(int idx) const { return data[idx]; }
void EnemyArray::removeAt(int idx) { delete data[idx]; for (int i = idx;i < cnt - 1;++i) data[i] = data[i + 1]; --cnt; }
int EnemyArray::size() const { return cnt; }
void EnemyArray::clear() { for (int i = 0;i < cnt;++i) delete data[i]; cnt = 0; }
void EnemyArray::resize() { int ncap = cap * 2; Enemy** nd = (Enemy**)std::malloc(sizeof(Enemy*) * ncap); for (int i = 0;i < cnt;++i) nd[i] = data[i]; std::free(data); data = nd; cap = ncap; }