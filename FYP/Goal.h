#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Goal
{
public:
	Goal(std::string filepath, sf::Vector2f size, sf::Vector2f position);
	~Goal();

	void draw(sf::RenderWindow &window);
	sf::RectangleShape getShape();
private:
	sf::Texture m_texture;
	sf::RectangleShape m_shape;

};

