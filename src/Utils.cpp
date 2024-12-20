#include "../include/Utils.hpp"
#include <cmath>

float distance(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

sf::Vector2f normalize(const sf::Vector2f &vector)
{
    float len = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    return len == 0 ? sf::Vector2f(0, 0) : sf::Vector2f(vector.x / len, vector.y / len);
}
