#include "../include/GameConstants.hpp"
#include "../include/Entities/Player.hpp"
#include "../include/Entities/Bullet.hpp"
#include "../include/Utils.hpp"
#include <iostream>

Player::Player()
{
    shape.setRadius(20);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    destination = shape.getPosition();
    health = PLAYER_HEALTH;
    ammo = PLAYER_AMMO;
}

void Player::setDestination(sf::Vector2f &destination)
{
    this->destination = destination;
}

void Player::shoot(std::vector<Bullet> &bullets, sf::Vector2f target)
{
    if (ammo > 0)
    {
        bullets.push_back(Bullet(shape.getPosition(), target - shape.getPosition()));
        ammo--;
    }
}

void Player::update(float deltaTime) {
    sf::Vector2f direction = destination - shape.getPosition();

    if (distance(shape.getPosition(), destination) > 1)
    {
        shape.move(normalize(direction) * PLAYER_SPEED * deltaTime);
    }
}
