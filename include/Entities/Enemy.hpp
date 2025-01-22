#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include "../GameObject.hpp"
#include "Bullet.hpp"

class Enemy : public GameObject
{
private:
    sf::Vector2f destination;
    int health;
    int ammo;

public:
    Enemy(sf::Vector2f position);
    void update(float deltaTime) override;
    void shoot(std::vector<Bullet> &bullets, sf::Vector2f target);
    void setDestination(const sf::Vector2f &destination);
    int getHealth() const { return health; }
    int getAmmo() const { return ammo; }
    void markAsDestroyed() { health = 0; }
    bool isDestroyed() const { return health <= 0; }



};
#endif
