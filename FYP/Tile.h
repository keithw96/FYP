#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Tile
{
public:
	Tile(std::string filePath, sf::Vector2f size, sf::Vector2f pos);
	~Tile();

	void draw(sf::RenderWindow& window);

	sf::RectangleShape getShape();
	sf::Vector2f getHalfSize();
	sf::Vector2f getPos();
private:

	sf::Texture m_texture;
	sf::RectangleShape m_shape;
	sf::Vector2f m_pos;
};
