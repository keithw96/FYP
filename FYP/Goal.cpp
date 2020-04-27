#include "Goal.h"

Goal::Goal(std::string filepath, sf::Vector2f size, sf::Vector2f position)
{
	//if (!m_texture.loadFromFile("./Resources/Sprites/Flag.png"))
	if (!m_texture.loadFromFile(filepath))
	{
		std::cout << "Failed to load Flag Texture" << std::endl;
	}
	m_shape.setPosition(position);
	m_shape.setSize(size);
	
	m_shape.setTexture(&m_texture);
	m_shape.setOrigin(m_shape.getSize() / 2.0f);
}

Goal::~Goal()
{
}

void Goal::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

sf::RectangleShape Goal::getShape()
{
	return m_shape;
}
