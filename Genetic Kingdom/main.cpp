#include <SFML/Graphics.hpp>
#include <optional>

// Función que detecta si dos rectángulos se cruzan
bool checkCollision(const sf::FloatRect& a, const sf::FloatRect& b)
{
    return (a.position.x < b.position.x + b.size.x &&
        a.position.x + a.size.x > b.position.x &&
        a.position.y < b.position.y + b.size.y &&
        a.position.y + a.size.y > b.position.y);
}




int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Mini juego SFML 3.0.0");

    // Crear el jugador
    sf::RectangleShape player({ 50.f, 50.f });
    player.setFillColor(sf::Color::Blue);
    player.setPosition({ 100.f, 100.f });

    // Crear la meta
    sf::RectangleShape goal({ 50.f, 50.f });
    goal.setFillColor(sf::Color::Green);
    goal.setPosition({ 600.f, 400.f });

    // Velocidad de movimiento (pixeles por segundo)
    float speed = 200.f;

    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        // Manejo de eventos
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Movimiento del jugador
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            player.move({ 0.f, -speed * deltaTime });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            player.move({ 0.f, speed * deltaTime });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            player.move({ -speed * deltaTime, 0.f });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            player.move({ speed * deltaTime, 0.f });


        // Detectar colisión
        if (checkCollision(player.getGlobalBounds(), goal.getGlobalBounds()))
        {
            player.setFillColor(sf::Color::Red);
        }


        // Dibujar
        window.clear();
        window.draw(player);
        window.draw(goal);
        window.display();
    }

    return 0;
}
