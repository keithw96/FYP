#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
class MovingPlatform
{
public:
    
    MovingPlatform(sf::Vector2f pos, int topHeight, int bottomHeight);
    ~MovingPlatform();

    void update();
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPos();
    sf::Vector2f getHalfSize();
    sf::RectangleShape getShape();
private:

    sf::RectangleShape m_shape;
    sf::Texture m_texture;

    int m_topHeight;
    int m_bottomHeight;
    int m_speed;
    bool m_moveUp;

};

