#include "Enemy.hpp"
#include <cmath>

// Setter para colorear el enemigo
void Enemy::setColor(const sf::Color& color) {
    shape.setFillColor(color);
}

Enemy::Enemy(GridMap& map, float cellSize, float speed)
    : gridMap(map), cellSize(cellSize), speed(speed)
{
    auto s = gridMap.getStartPosition();
    currentRow = s.y; currentCol = s.x;
    shape.setSize({ cellSize * 0.8f, cellSize * 0.8f });
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition({ currentCol * cellSize + cellSize * 0.1f,
                       currentRow * cellSize + cellSize * 0.1f });
}

bool Enemy::isAlive() const { return alive; }
void Enemy::resetPath() { pathCalculated = false; }

void Enemy::update(float dt) {
    if (!alive) return;
    if (!pathCalculated) { calculatePath(); pathCalculated = true; pathIndex = 1; }
    if (pathIndex < path.size()) {
        Node* t = path.get(pathIndex);
        sf::Vector2f tp = { t->col * cellSize + cellSize * 0.1f, t->row * cellSize + cellSize * 0.1f };
        sf::Vector2f cp = shape.getPosition();
        sf::Vector2f dir = tp - cp;
        float d = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (d > speed * dt) {
            dir /= d;
            shape.move(dir * speed * dt);
        }
        else {
            shape.setPosition(tp);
            currentRow = t->row; currentCol = t->col;
            ++pathIndex;
            if (pathIndex >= path.size()) alive = false;
        }
    }
}

void Enemy::draw(sf::RenderWindow& window) const { if (alive) window.draw(shape); }

void Enemy::calculatePath() {
    openList.clear(); closedList.clear(); path.clear();
    Node* s = &gridMap.getNode(currentRow, currentCol);
    auto g = gridMap.getGoalPosition();
    Node* gn = &gridMap.getNode(g.y, g.x);
    s->gCost = 0; s->hCost = heuristic(s, gn); s->parent = nullptr;
    openList.push_back(s);
    while (openList.size() > 0) {
        Node* c = getLowestFCostNode();
        if (c == gn) { reconstructPath(gn); return; }
        for (int i = 0;i < openList.size();++i) if (openList.get(i) == c) { openList.removeAt(i);break; }
        closedList.push_back(c);
        auto nbs = gridMap.getNeighbors(*c);
        for (Node* nbr : nbs) {
            if (isInList(closedList, nbr)) continue;
            float tg = c->gCost + 1;
            if (!isInList(openList, nbr) || tg < nbr->gCost) {
                nbr->gCost = tg;
                nbr->hCost = heuristic(nbr, gn);
                nbr->parent = c;
                if (!isInList(openList, nbr)) openList.push_back(nbr);
            }
        }
    }
}

float Enemy::heuristic(Node* a, Node* b) const {
    return std::abs(a->row - b->row) + std::abs(a->col - b->col);
}

Node* Enemy::getLowestFCostNode() {
    Node* best = openList.get(0);
    for (int i = 1;i < openList.size();++i) {
        Node* n = openList.get(i);
        if (n->fCost() < best->fCost() || (n->fCost() == best->fCost() && n->hCost < best->hCost)) best = n;
    }
    return best;
}

bool Enemy::isInList(const NodeVector& list, Node* node) const {
    for (int i = 0;i < list.size();++i) if (list.get(i) == node) return true;
    return false;
}

void Enemy::reconstructPath(Node* endNode) {
    std::vector<Node*> rev;
    for (Node* cur = endNode;cur;cur = cur->parent) rev.push_back(cur);
    for (auto it = rev.rbegin(); it != rev.rend(); ++it) path.push_back(*it);
}