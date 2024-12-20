#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game
{
private:
    sf::RenderWindow window;

public:
    Game();

    void run();
    void processEvents();
    void update();
    void render();
};

#endif
