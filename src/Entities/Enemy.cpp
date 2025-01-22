#include "../include/GameConstants.hpp"
#include "../include/Entities/Enemy.hpp"
#include "../include/Entities/Bullet.hpp"
#include "../include/Utils.hpp"
#include <iostream>

Enemy::Enemy(sf::Vector2f position)
{
    shape.setRadius(20);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(position);

    destination = position;
}

void Enemy::shoot(std::vector<Bullet> &bullets, sf::Vector2f target)
{
    if (ammo > 0)
    {
        bullets.push_back(Bullet(shape.getPosition(), target - shape.getPosition()));
        ammo--;
    }
}

void Enemy::update(float deltaTime) {
    sf::Vector2f direction = destination - shape.getPosition();

    if (distance(shape.getPosition(), destination) > 1)
    {
        shape.move(normalize(direction) * ENEMY_SPEED * deltaTime);
    }
}

void Enemy::setDestination(const sf::Vector2f &destination)
{
    this->destination = destination;
}
