#include "../include/Entities/Bullet.hpp"
#include "../include/GameConstants.hpp"
#include "../include/Utils.hpp"

Bullet::Bullet(const sf::Vector2f &position, const sf::Vector2f &direction)
{
    shape.setRadius(5);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(position);

    velocity = normalize(direction) * BULLET_SPEED;
}

void Bullet::update(float deltaTime)
{
    shape.move(velocity * deltaTime);
}

void Bullet::render(sf::RenderWindow &window)
{
    window.draw(shape);
}
