#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics/RenderWindow.hpp>

class GameObject
{
protected:
    sf::CircleShape shape;

public:
    virtual ~GameObject() = default;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow &window) { window.draw(shape); }
    virtual sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
    void setPosition(const sf::Vector2f &position) { shape.setPosition(position); }
    void setColor(const sf::Color &color) { shape.setFillColor(color); }
    sf::Vector2f getPosition() const { return shape.getPosition(); }
};

#endif
