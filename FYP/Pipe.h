#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Pipe
{
public:

	Pipe(std::string path, sf::Vector2f pos, sf::Vector2f size);
	~Pipe();

	void draw(sf::RenderWindow& window);

	sf::RectangleShape getShape();
	sf::Vector2f getHalfSize();
	sf::Vector2f getPos();
private:

	sf::RectangleShape m_shape;
	sf::Texture m_texture;
	sf::Vector2f m_position;
};

