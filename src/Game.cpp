#include "../include/Game.hpp"
#include <iostream>
#include <GameConstants.hpp>

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Base Defense")
{
    window.setFramerateLimit(60);
    state = GameState::MainMenu;

    textManager.setupText(mainMenuText, "Base Defense\n\n\nPress Enter to Start\n\nPress Escape to Exit", 24, sf::Color::White, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    textManager.setupText(pauseText, "Paused\n\n\nPress Escape to Resume\n\nPress Enter to Return to Menu", 24, sf::Color::White, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    textManager.setupText(gameOverText, "Game Over\n\n\nPress Enter to Return to Menu", 24, sf::Color::White, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    textManager.setupText(scoreText, "Score: 0\nHealth: 0\nAmmo: 0", 18, sf::Color::White, 50, 50);
}

void Game::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        processEvents();

        if (state == GameState::Playing)
        {
            update(deltaTime);
        }

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

        switch (state)
        {
        case GameState::MainMenu:
            handleMainMenuEvents(event);
            break;
        case GameState::Playing:
            handlePlayingEvents(event);
            break;
        case GameState::Paused:
            handlePausedEvents(event);
            break;
        case GameState::GameOver:
            handleGameOverEvents(event);
            break;
        }
    }
}

void Game::update(float deltaTime)
{
    player.update(deltaTime);

    for (auto &bullet : bullets)
    {
        bullet.update(deltaTime);
    }

    if (enemies.size() < 5)
    {
        spawnEnemy();
    }

    for (auto &enemy : enemies)
    {
        enemy.setDestination(player.getPosition());
        enemy.update(deltaTime);
    }

    for (auto &enemyBullet : enemyBullets)
    {
        enemyBullet.update(deltaTime);
    }


    checkCollisions();

    updateHUD();

    if (player.getHealth() <= 0)
    {
        state = GameState::GameOver;

        textManager.setupText(
            gameOverText,
            "Game Over\n\n\nPress Enter to Return to Menu\n\nScore: " + std::to_string(score),
            24,
            sf::Color::White,
            WINDOW_WIDTH / 2,
            WINDOW_HEIGHT / 2
        );
        // Resetar o jogo
        player = Player();
        bullets.clear();
        enemies.clear();
        enemyBullets.clear();
        score = 0;
    }
}

void Game::render()
{
    window.clear();

    if (state == GameState::MainMenu)
    {
        window.draw(mainMenuText);
    }
    else if (state == GameState::Playing)
    {
        player.render(window);

        for (auto &bullet : bullets)
        {
            bullet.render(window);
        }

        for (auto &enemy : enemies)
        {
            enemy.render(window);
        }

        window.draw(scoreText);
    }
    else if (state == GameState::Paused)
    {
        window.draw(pauseText);
    }
    else if (state == GameState::GameOver)
    {
        window.draw(gameOverText);
    }

    window.display();
}

void Game::handleMainMenuEvents(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
    {
        state = GameState::Playing;
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        window.close();
    }
}

void Game::handlePlayingEvents(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        state = GameState::Paused;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2f target = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        player.setDestination(target);
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        sf::Vector2f target = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        std::cout << "Shooting at " << target.x << ", " << target.y << std::endl;
        player.shoot(bullets, target);
    }
}

void Game::handlePausedEvents(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        state = GameState::Playing;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
    {
        state = GameState::MainMenu;
    }
}

void Game::handleGameOverEvents(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
    {
        state = GameState::MainMenu;
    }
}

void Game::updateHUD()
{
    scoreText.setString("Score: " + std::to_string(score) +
                        "\nHealth: " + std::to_string(player.getHealth()) +
                        "\nAmmo: " + std::to_string(player.getAmmo()));
}

void Game::spawnEnemy()
{
    sf::Vector2f position;
    int side = rand() % 4;

    switch (side)
    {
    case 0:
        position = sf::Vector2f(rand() % WINDOW_WIDTH, 0);
        break;
    case 1:
        position = sf::Vector2f(rand() % WINDOW_WIDTH, WINDOW_HEIGHT);
        break;
    case 2:
        position = sf::Vector2f(0, rand() % WINDOW_HEIGHT);
        break;
    case 3:
        position = sf::Vector2f(WINDOW_WIDTH, rand() % WINDOW_HEIGHT);
        break;
    }

    enemies.push_back(Enemy(position));
}

void Game::checkCollisions()
{
    // Verificar colisões entre balas do jogador e inimigos
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();)
    {
        bool bulletDestroyed = false;

        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();)
        {
            if (bulletIt->getBounds().intersects(enemyIt->getBounds()))
            {
                bulletIt = bullets.erase(bulletIt);
                enemyIt = enemies.erase(enemyIt);
                score += 10; // Incrementar a pontuação
                bulletDestroyed = true;
                break;
            }
            else
            {
                ++enemyIt;
            }
        }

        if (!bulletDestroyed)
        {
            ++bulletIt;
        }
    }

    // Verificar colisões entre o jogador e inimigos
    for (auto &enemy : enemies)
    {
        if (player.getBounds().intersects(enemy.getBounds()))
        {
            player.takeDamage(10);
            enemy.markAsDestroyed();
        }
    }

    // Remover inimigos destruídos
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                 [](const Enemy &enemy)
                                 { return enemy.isDestroyed(); }),
                  enemies.end());
}

void Game::setupUI()
{
    textManager.setupText(mainMenuText, "Base Defense\n\n\nPress Enter to Start\n\nPress Escape to Exit", 24, sf::Color::White, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    textManager.setupText(pauseText, "Paused\n\n\nPress Escape to Resume\n\nPress Enter to Return to Menu", 24, sf::Color::White, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    textManager.setupText(gameOverText, "Game Over\n\n\nPress Enter to Return to Menu", 24, sf::Color::White, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    textManager.setupText(scoreText, "Score: 0\nHealth: 0\nAmmo: 0", 18, sf::Color::White, 50, 50);
}
