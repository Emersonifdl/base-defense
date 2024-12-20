#include "../include/Game.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "SFML window") {
}


void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f destination = window.mapPixelToCoords(mousePosition);
            player.setDestination(destination);
        }
    }
}

void Game::update() {
    float deltaTime  = clock.restart().asSeconds();

    player.update(deltaTime);
}

void Game::render() {
    window.clear();
    player.render(window);
    window.display();
}
