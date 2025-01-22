#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Entities/Player.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Bullet.hpp"

class TextManager {
private:
    sf::Font font;

public:
    TextManager() {
        if (!font.loadFromFile("../assets/fonts/super_squad.ttf")) {
            throw std::runtime_error("Failed to load font.");
        }
    }

    void setupText(sf::Text& text, const std::string& str, int size, const sf::Color& color, float x, float y) {
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(size);
        text.setFillColor(color);
        text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
        text.setPosition(x, y);
    }
};

enum class GameState {
    MainMenu,
    Playing,
    Paused,
    GameOver
};
class Game
{
private:
    sf::RenderWindow window;
    GameState state;
    Player player;
    sf::Clock clock;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    std::vector<Bullet> enemyBullets;
    int score = 0;

    TextManager textManager;
    sf::Text mainMenuText;
    sf::Text pauseText;
    sf::Text gameOverText;
    sf::Text scoreText;

    void setupUI();

    // Processamento de eventos separado da lógica de jogo
    void handleMainMenuEvents(const sf::Event& event);
    void handlePlayingEvents(const sf::Event& event);
    void handlePausedEvents(const sf::Event& event);
    void handleGameOverEvents(const sf::Event& event);

    void processEvents();
    void update(float deltaTime);
    void render();
    void spawnEnemy();
    void checkCollisions();
    void updateHUD();
    // void resetGame();

public:
    Game();
    void run();
};

#endif
