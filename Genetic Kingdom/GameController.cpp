#include "GameController.hpp"

GameController::GameController(sf::RenderWindow& window, int rows, int cols, float cellSize)
    : window(window)
    , map(rows, cols, cellSize)            // Inicializa GridMap
    , player(200, 10)
    , waveMgr(map, cellSize, 120.f, 5, 10, font)
    , placementMgr(cellSize, font)
{
    if (!font.openFromFile("Nexa-Heavy.ttf")) {
        // Manejo de error de fuente
    }
    window.setFramerateLimit(60);
}

void GameController::run() {  
   while (window.isOpen()) {  
       while (auto ev = window.pollEvent()) {  
           if (ev && ev->is<sf::Event::Closed>()) window.close();  
           handleEvent(&(*ev));  
       }  
       float dt = clock.restart().asSeconds();  
       update(dt);  
       draw();  
   }  
}

void GameController::handleEvent(const sf::Event* ev) {
    if (!ev) return;
    if (auto mb = ev->getIf<sf::Event::MouseButtonPressed>()) {
        if (mb->button == sf::Mouse::Button::Left) {
            int x = mb->position.x;
            int y = mb->position.y;
            if (placementMgr.isActive()) {
                Tower* t = placementMgr.processClick(x, y);
                if (t) {
                    map.toggleWalkable(selectedRow, selectedCol);
                    if (!map.isPathAvailable() || !player.spendGold(t->getCost())) {
                        map.toggleWalkable(selectedRow, selectedCol);
                        delete t;
                    }
                    else {
                        towers.push_back(t);
                        // Reiniciar rutas enemigas
                        waveMgr.resetAllEnemyPaths();
                    }
                }
            }
            else {
                int col = x / static_cast<int>(placementMgr.getCellSize());
                int row = y / static_cast<int>(placementMgr.getCellSize());
                if (row < map.getRows() && col < map.getCols()) {
                    selectedRow = row;
                    selectedCol = col;
                    placementMgr.requestPlacement(row, col);
                }
            }
        }
    }
}

void GameController::update(float dt) {
    waveMgr.update(dt);
    for (auto* t : towers) t->update(dt);
}

void GameController::draw() {
    window.clear();
    map.draw(window);
    for (auto* t : towers) t->draw(window);
    waveMgr.draw(window);
    placementMgr.draw(window);
    window.display();
}