#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics/RenderWindow.hpp>

class Entity
{
public:
    virtual ~Entity() = default;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow &window) = 0;
};

#endif
