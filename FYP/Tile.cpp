#include "Tile.h"

Tile::Tile(std::string filePath, sf::Vector2f size, sf::Vector2f pos)
{
	if (!m_texture.loadFromFile(filePath))
	{
		std::cout << "Failed to load player sprite" << std::endl;
	}
	m_shape.setTexture(&m_texture);
	m_shape.setSize(sf::Vector2f(size));
	m_shape.setPosition(sf::Vector2f(pos));
	m_shape.setOrigin(m_shape.getSize() / 2.0f);
}

Tile::~Tile()
{
}

void Tile::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

sf::RectangleShape Tile::getShape()
{
	return m_shape;
}

sf::Vector2f Tile::getHalfSize()
{
	return m_shape.getSize() / 2.0f;
}

sf::Vector2f Tile::getPos()
{
	return m_shape.getPosition();
}

