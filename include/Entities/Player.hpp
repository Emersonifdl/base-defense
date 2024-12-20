#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include <SFML/Graphics/CircleShape.hpp>

class Player : public Entity
{
private:
    // sf::Sprite sprite;
    sf::CircleShape shape;
    sf::Vector2f destination;

public:
    Player();
    void update(float deltaTime) override;
    void render(sf::RenderWindow &window) override;
    void setDestination(sf::Vector2f &destination);
};
#endif
