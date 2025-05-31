#include "GameController.hpp"
#include "SimpleVector.hpp"

GameController::GameController(sf::RenderWindow& w,int rows,int cols,float cellSize,const sf::Font& font)
    : upgradeMgr(w.getSize().x, w.getSize().y, font)   
    , window(w)                                         
    , map(rows, cols, cellSize)                         
    , player(400, 20)
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
    gameOverBackground.setFillColor(sf::Color(0, 0, 0, 255));
    gameOverText.setString("Perdiste!");
    gameOverText.setCharacterSize(64);
    gameOverText.setFillColor(sf::Color::White);
    auto bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
    gameOverText.setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
}

void GameController::run() {
    while (window.isOpen()) {
        while (auto ev = window.pollEvent()) {
            if (ev && ev->is<sf::Event::Closed>()) window.close();
            handleEvent(&*ev);
        }
        float dt = clock.restart().asSeconds();
        update(dt);
        draw();
    }
}

void GameController::handleEvent(const sf::Event* ev) {
    if (!ev || gameOver) return;
    if (auto mb = ev->getIf<sf::Event::MouseButtonPressed>()) {
        if (mb->button != sf::Mouse::Button::Left) return;
        int x = mb->position.x;
        int y = mb->position.y;

        // 1) Popup de mejora activo
        if (upgradeMgr.isActive()) {
            int res = upgradeMgr.processClick(x, y);
            if (res == 1) {
                Tower* t = upgradeMgr.getSelectedTower();
                int price = t->getUpgradeCost();
                if (player.spendGold(price)) t->upgrade();
            }
            return;
        }

        // 2) Popup de colocación activo
        if (placementMgr.isActive()) {
            Tower* newT = placementMgr.processClick(x, y);
            if (newT) {
                map.toggleWalkable(selectedRow, selectedCol);
                if (!map.isPathAvailable() || !player.spendGold(newT->getCost())) {
                    map.toggleWalkable(selectedRow, selectedCol);
                    delete newT;
                }
                else {
                    towers.push_back(newT);
                    waveMgr.resetAllEnemyPaths();
                }
            }
            return;
        }

        // 3) Clic sobre torre existente -> iniciar mejora
        float cs = placementMgr.getCellSize();
        int col = x / static_cast<int>(cs);
        int row = y / static_cast<int>(cs);
        for (size_t i = 0; i < towers.size(); ++i) {
            Tower* t = towers[i];
            auto gp = t->getGridPosition();  // {col, row}
            if (gp.x == col && gp.y == row) {
                if (upgradeMgr.requestUpgrade(t)) {
                    return;
                }
            }
        }

        // 4) Clic en celda vacía -> iniciar colocación
        if (row >= 0 && row < map.getRows() && col >= 0 && col < map.getCols()) {
            selectedRow = row;
            selectedCol = col;
            placementMgr.requestPlacement(row, col);
        }
    }
}

void GameController::update(float dt) {
    waveMgr.update(dt, player);
    if (player.getLives() <= 0) gameOver = true;
    SimpleVector enem = waveMgr.getEnemyList();
    for (size_t i = 0;i < towers.size();++i)
        towers[i]->update(enem, dt, bullets);
    // actualizar y eliminar balas expiradas
    for (size_t i = 0;i < bullets.size();) {
        bullets[i].update(dt);
        if (bullets[i].isExpired()) bullets.removeAt(i);
        else ++i;
    }
}

void GameController::draw() {
    window.clear();
    map.draw(window);
    for (size_t i = 0;i < towers.size();++i) towers[i]->draw(window);
    waveMgr.draw(window);
    goldText.setString("Oro: " + std::to_string(player.getGold()));
    window.draw(goldText);
    livesText.setString("Vidas: " + std::to_string(player.getLives()));
    window.draw(livesText);
    for (size_t i = 0;i < bullets.size();++i)
        window.draw(bullets[i].getShape());
    if (gameOver) {
        window.draw(gameOverBackground);
        window.draw(gameOverText);
    }
    placementMgr.draw(window);
    upgradeMgr.draw(window);
    window.display();
}