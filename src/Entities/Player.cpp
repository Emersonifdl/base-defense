#include "../include/Entities/Player.hpp"
#include "../include/utils/GameConstants.hpp"

Player::Player()
{
    shape.setRadius(20);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    destination = shape.getPosition();
}

void Player::setDestination(sf::Vector2f &destination)
{
    this->destination = destination;
}

void Player::update(float deltaTime)
{
    sf::Vector2f direction = normalize(destination - shape.getPosition());
    if (distance(shape.getPosition(), destination) > 1.f)
    {
        shape.move(direction * PLAYER_SPEED * deltaTime);
    }
}

void Player::render(sf::RenderWindow &window)
{
    window.draw(shape);
}
