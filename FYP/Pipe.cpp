#include "Pipe.h"

Pipe::Pipe(std::string path, sf::Vector2f pos, sf::Vector2f size)
{
	if (!m_texture.loadFromFile(path))
	{
		std::cout << "Error Loading pipe texture" << std::endl;
	}
	m_shape.setTexture(&m_texture);
	m_shape.setSize(sf::Vector2f(size));
	m_shape.setPosition(sf::Vector2f(pos));
	m_shape.setOrigin(m_shape.getSize() / 2.0f);
}

Pipe::~Pipe()
{
}

void Pipe::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

sf::RectangleShape Pipe::getShape()
{
	return m_shape;
}

sf::Vector2f Pipe::getHalfSize()
{
	return m_shape.getSize() / 2.0f;
}

sf::Vector2f Pipe::getPos()
{
	return m_shape.getPosition();
}