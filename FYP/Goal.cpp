#include "Goal.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="filepath"></param>
/// <param name="size"></param>
/// <param name="position"></param>
Goal::Goal(std::string filepath, sf::Vector2f size, sf::Vector2f position)
{
	if (!m_texture.loadFromFile(filepath))
	{
		std::cout << "Failed to load Flag Texture" << std::endl;
	}
	m_shape.setPosition(position);
	m_shape.setSize(size);
	
	m_shape.setTexture(&m_texture);
	m_shape.setOrigin(m_shape.getSize() / 2.0f);
}

/// <summary>
/// Deconstructor
/// </summary>
Goal::~Goal()
{

}

/// <summary>
/// Render the goal to the window
/// </summary>
/// <param name="window"></param>
void Goal::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

/// <summary>
/// Returns the shape
/// </summary>
/// <returns></returns>
sf::RectangleShape Goal::getShape()
{
	return m_shape;
}
