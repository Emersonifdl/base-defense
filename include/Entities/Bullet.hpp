#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "../GameObject.hpp"

class Bullet : public GameObject
{
private:
    sf::Vector2f velocity;

public:
    Bullet(const sf::Vector2f &position, const sf::Vector2f &direction);
    void update(float deltaTime) override;
};

#endif
