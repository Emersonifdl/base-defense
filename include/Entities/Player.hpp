#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include "Entity.hpp"
#include "Bullet.hpp"

class Player : public Entity
{
private:
    // sf::Sprite sprite;
    sf::CircleShape shape;
    sf::Vector2f destination;
    int health;
    int ammo;

public:
    Player();
    void update(float deltaTime) override;
    void render(sf::RenderWindow &window) override;
    void setDestination(sf::Vector2f &destination);
    void shoot(std::vector<Bullet> &bullets, sf::Vector2f target);

};
#endif
