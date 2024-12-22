#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "Entity.hpp"

class Bullet : public Entity
{
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;

public:
    Bullet(const sf::Vector2f &position, const sf::Vector2f &direction);
    void update(float deltaTime) override;
    void render(sf::RenderWindow &window) override;
};

#endif
