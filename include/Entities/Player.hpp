#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include "../GameObject.hpp"
#include "Bullet.hpp"

class Player : public GameObject
{
private:
    sf::Vector2f destination;
    int health;
    int ammo;

public:
    Player();
    void update(float deltaTime) override;
    void setDestination(sf::Vector2f &destination);
    void shoot(std::vector<Bullet> &bullets, sf::Vector2f target);
    int getHealth() const { return health; }
    int getAmmo() const { return ammo; }
    void takeDamage(int damage) { health -= damage; }

};
#endif
