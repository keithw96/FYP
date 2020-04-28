#include "Pipe.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="path"></param>
/// <param name="pos"></param>
/// <param name="size"></param>
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

/// <summary>
/// Deconstructor
/// </summary>
Pipe::~Pipe()
{
}

/// <summary>
/// Render the pipe's shape
/// </summary>
/// <param name="window"></param>
void Pipe::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

/// <summary>
/// Returns the pipes shape
/// </summary>
/// <returns></returns>
sf::RectangleShape Pipe::getShape()
{
	return m_shape;
}

/// <summary>
/// Returns half the size of the pipe shape
/// </summary>
/// <returns></returns>
sf::Vector2f Pipe::getHalfSize()
{
	return m_shape.getSize() / 2.0f;
}

/// <summary>
/// Returns the position of the pipe shape
/// </summary>
/// <returns></returns>
sf::Vector2f Pipe::getPos()
{
	return m_shape.getPosition();
}