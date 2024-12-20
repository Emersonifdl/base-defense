#include "../include/Game.hpp"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Base Defense")
{
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2f destination = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            player.setDestination(destination);
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {
            sf::Vector2f target = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            std::cout << "Shooting at " << target.x << ", " << target.y << std::endl;
            player.shoot(bullets, target);
        }
    }
}

void Game::update()
{
    float deltaTime = clock.restart().asSeconds();

    player.update(deltaTime);

    for (auto &bullet : bullets)
    {
        bullet.update(deltaTime);
    }
}

void Game::render()
{
    window.clear();

    player.render(window);

    for (auto &bullet : bullets)
    {
        bullet.render(window);
    }

    window.display();
}
