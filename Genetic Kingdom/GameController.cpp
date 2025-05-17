#include "GameController.hpp"

GameController::GameController(sf::RenderWindow& window,
    int rows,
    int cols,
    float cellSize,
    const sf::Font& font)
    : window(window)
    , map(rows, cols, cellSize)
    , player(200, 10)
    , waveMgr(map, cellSize, 120.f, 5, 10, font)
    , placementMgr(cellSize, font)
    , goldText(font)
{
    window.setFramerateLimit(60);

    // Configurar texto de oro
    goldText.setCharacterSize(24);
    goldText.setFillColor(sf::Color::White);
    goldText.setPosition(sf::Vector2f(150.f, rows * cellSize + 5.f));
}

void GameController::run() {  
   while (window.isOpen()) {  
       // Procesar eventos  
       while (auto ev = window.pollEvent()) {  
           if (ev && ev->is<sf::Event::Closed>()) {  
               window.close();  
           }  
           if (ev) {  
               handleEvent(&(*ev));  
           }  
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
                    // Intentar colocar torre como obstáculo
                    map.toggleWalkable(selectedRow, selectedCol);
                    if (!map.isPathAvailable() || !player.spendGold(t->getCost())) {
                        // Revertir si bloqueo o falta de oro
                        map.toggleWalkable(selectedRow, selectedCol);
                        delete t;
                    }
                    else {
                        towers.push_back(t);
                        waveMgr.resetAllEnemyPaths();
                    }
                }
            }
            else {
                // Iniciar solicitud de colocación
                float cs = placementMgr.getCellSize();
                int col = x / static_cast<int>(cs);
                int row = y / static_cast<int>(cs);
                if (row >= 0 && row < map.getRows() && col >= 0 && col < map.getCols()) {
                    selectedRow = row;
                    selectedCol = col;
                    placementMgr.requestPlacement(row, col);
                }
            }
        }
    }
}

void GameController::update(float dt) {
    waveMgr.update(dt, player);

    // obtener punteros vigentes
    auto enem = waveMgr.getEnemyList();

    // actualizar torres (añade balas)
    for (auto* t : towers)
        t->update(enem, dt, bullets);

    // actualizar y purgar balas
    for (auto it = bullets.begin(); it != bullets.end();) {
        it->update(dt);
        if (it->isExpired()) it = bullets.erase(it);
        else ++it;
    }
}

void GameController::draw() {
    window.clear();
    map.draw(window);
    for (auto* t : towers) t->draw(window);
    waveMgr.draw(window);
    goldText.setString("Oro: " + std::to_string(player.getGold()));
    window.draw(goldText);

    // dibujar balas
    for (auto& b : bullets)
        window.draw(b.getShape());

    placementMgr.draw(window);
    window.display();
}