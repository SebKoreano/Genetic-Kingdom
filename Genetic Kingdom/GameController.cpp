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
    , livesText(font)
    , gameOver(false)
    , gameOverBackground()
    , gameOverText(font)
{
    window.setFramerateLimit(60);

    // Configurar texto de oro
    goldText.setCharacterSize(24);
    goldText.setFillColor(sf::Color::White);
    goldText.setPosition(sf::Vector2f(145.f, rows * cellSize + 5.f));
    // Configurar texto de vidas
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(sf::Vector2f(280.f, rows * cellSize + 5.f));
    // Configure game over overlay
    gameOverBackground.setSize(sf::Vector2f(window.getSize()));
    gameOverBackground.setFillColor(sf::Color(0, 0, 0, 150));
    gameOverText.setString("Perdiste!");
    gameOverText.setCharacterSize(64);
    gameOverText.setFillColor(sf::Color::White);
    auto bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
    gameOverText.setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
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
    if (player.getLives() <= 0) gameOver = true;

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

	// dibujar texto de oro y vidas
    goldText.setString("Oro: " + std::to_string(player.getGold()));
    window.draw(goldText);
    livesText.setString("Vidas: " + std::to_string(player.getLives()));
    window.draw(livesText);

    // dibujar balas
    for (auto& b : bullets)
        window.draw(b.getShape());

    if (gameOver) {
        window.draw(gameOverBackground);
        window.draw(gameOverText);
    }

    placementMgr.draw(window);
    window.display();
}