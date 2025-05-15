#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(GridMap& map, float cellSize, float speed)
    : gridMap(map), cellSize(cellSize), speed(speed)
{
    auto startPos = gridMap.getStartPosition();
    currentRow = startPos.y; currentCol = startPos.x;
    shape.setSize({ cellSize * 0.8f, cellSize * 0.8f });
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(sf::Vector2f(
        currentCol * cellSize + cellSize * 0.1f,
        currentRow * cellSize + cellSize * 0.1f
    ));
}

void Enemy::update(float dt)
{
    if (!pathCalculated) {
        calculatePath();
        pathCalculated = true;
        pathIndex = 1; // Empezar en el siguiente nodo
    }
    if (pathIndex < path.size()) {
        Node* target = path.get(pathIndex);
        sf::Vector2f targetPos(
            target->col * cellSize + cellSize * 0.1f,
            target->row * cellSize + cellSize * 0.1f
        );
        sf::Vector2f currentPos = shape.getPosition();
        sf::Vector2f dir = targetPos - currentPos;
        float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (dist > speed * dt) {
            dir /= dist;
            shape.move(dir * speed * dt);
        }
        else {
            shape.setPosition(targetPos);
            currentRow = target->row;
            currentCol = target->col;
            ++pathIndex;
            if (pathIndex >= path.size()) {
                // Llegó a meta: resucitar en inicio
                auto start = gridMap.getStartPosition();
                currentRow = start.y; currentCol = start.x;
                shape.setPosition(sf::Vector2f(
                    currentCol * cellSize + cellSize * 0.1f,
                    currentRow * cellSize + cellSize * 0.1f
                ));
                pathCalculated = false;
            }
        }
    }
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

void Enemy::calculatePath()
{
    openList.clear(); closedList.clear(); path.clear();
    Node* startNode = &gridMap.getNode(currentRow, currentCol);
    auto goalPos = gridMap.getGoalPosition();
    Node* goalNode = &gridMap.getNode(goalPos.y, goalPos.x);

    startNode->gCost = 0;
    startNode->hCost = heuristic(startNode, goalNode);
    startNode->parent = nullptr;
    openList.push_back(startNode);

    while (openList.size() > 0) {
        Node* current = getLowestFCostNode();
        if (current == goalNode) { reconstructPath(goalNode); return; }
        // mover a closed
        for (int i = 0; i < openList.size(); ++i)
            if (openList.get(i) == current) { openList.removeAt(i); break; }
        closedList.push_back(current);

        for (Node* nbr : gridMap.getNeighbors(*current)) {
            if (isInList(closedList, nbr)) continue;
            float tentativeG = current->gCost + 1;
            if (!isInList(openList, nbr) || tentativeG < nbr->gCost) {
                nbr->gCost = tentativeG;
                nbr->hCost = heuristic(nbr, goalNode);
                nbr->parent = current;
                if (!isInList(openList, nbr)) openList.push_back(nbr);
            }
        }
    }
}

float Enemy::heuristic(Node* a, Node* b)
{
    return std::abs(a->row - b->row) + std::abs(a->col - b->col);
}

Node* Enemy::getLowestFCostNode()
{
    Node* best = openList.get(0);
    for (int i = 1; i < openList.size(); ++i) {
        Node* n = openList.get(i);
        if (n->fCost() < best->fCost() || (n->fCost() == best->fCost() && n->hCost < best->hCost))
            best = n;
    }
    return best;
}

bool Enemy::isInList(const NodeVector& list, Node* node)
{
    for (int i = 0; i < list.size(); ++i)
        if (list.get(i) == node) return true;
    return false;
}

void Enemy::reconstructPath(Node* endNode)
{
    std::vector<Node*> rev;
    for (Node* cur = endNode; cur; cur = cur->parent) rev.push_back(cur);
    for (auto it = rev.rbegin(); it != rev.rend(); ++it) path.push_back(*it);
}