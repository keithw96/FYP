#include "Tile.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="filePath"></param>
/// <param name="pos"></param>
Tile::Tile(std::string filePath, sf::Vector2f pos)
{
	if (!m_texture.loadFromFile(filePath))
	{
		std::cout << "Failed to load player sprite" << std::endl;
	}
	m_shape.setTexture(&m_texture);
	m_shape.setSize(sf::Vector2f(32,32));
	m_shape.setPosition(sf::Vector2f(pos));
	m_shape.setOrigin(m_shape.getSize() / 2.0f);
}

/// <summary>
/// Deconstructor
/// </summary>
Tile::~Tile()
{
}

/// <summary>
/// Render the shape to the window
/// </summary>
/// <param name="window"></param>
void Tile::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

/// <summary>
/// Returns the shape
/// </summary>
/// <returns></returns>
sf::RectangleShape Tile::getShape()
{
	return m_shape;
}

/// <summary>
/// Returns the shape's half size
/// </summary>
/// <returns></returns>
sf::Vector2f Tile::getHalfSize()
{
	return m_shape.getSize() / 2.0f;
}

/// <summary>
/// Returns the shape's position
/// </summary>
/// <returns></returns>
sf::Vector2f Tile::getPos()
{
	return m_shape.getPosition();
}

