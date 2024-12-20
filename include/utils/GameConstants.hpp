#ifndef GAME_CONSTANTS_HPP
#define GAME_CONSTANTS_HPP

#include <SFML/System.hpp>
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PLAYER_SPEED = 100.f;

float distance(const sf::Vector2f &a, const sf::Vector2f &b);
sf::Vector2f normalize(const sf::Vector2f &vector);

float distance(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

sf::Vector2f normalize(const sf::Vector2f &vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0)
    {
        return sf::Vector2f(vector.x / length, vector.y / length);
    }
    return vector;
}
#endif
