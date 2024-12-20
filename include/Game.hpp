#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Entities/Player.hpp"
#include "Entities/Bullet.hpp"

class Game
{
private:
    sf::RenderWindow window;
    Player player;
    sf::Clock clock;
    std::vector<Bullet> bullets;

public:
    Game();

    void run();
    void processEvents();
    void update();
    void render();
};

#endif
