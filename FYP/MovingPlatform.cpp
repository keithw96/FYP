#include "MovingPlatform.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="pos"></param>
/// <param name="topHeight"></param>
/// <param name="bottomHeight"></param>
MovingPlatform::MovingPlatform(sf::Vector2f pos, int topHeight, int bottomHeight)
{
	if(!m_texture.loadFromFile("./Resources/Sprites/MovingPlatform.png"));
	{
		std::cout << "Could not load moving platform sprite" << std::endl;
	}
	m_shape.setPosition(pos);
	m_shape.setTexture(&m_texture);
	m_shape.setSize(sf::Vector2f(96, 16));
	m_shape.setOrigin(m_shape.getSize() / 2.0f);

	m_topHeight = topHeight;
	m_bottomHeight = bottomHeight;
	m_speed = -3;
	m_moveUp = true;
}

/// <summary>
/// Deconstructor
/// </summary>
MovingPlatform::~MovingPlatform()
{
}

/// <summary>
/// Update the platforms movement
/// Move up if it's y position is less than top height and m_moveUp is true
/// 
/// Move down if it's y position is greater than bottom height and m_moveUp is false
/// </summary>
void MovingPlatform::update()
{
	if (m_shape.getPosition().y < m_topHeight && m_moveUp)
	{
		m_speed *= -1;
		m_moveUp = false;
	}
	else if (m_shape.getPosition().y > m_bottomHeight && !m_moveUp)
	{
		m_speed *= -1;
		m_moveUp = true;
	}

	m_shape.move(sf::Vector2f(0, m_speed));
}

/// <summary>
/// Render the shape to the render window
/// </summary>
/// <param name="window"></param>
void MovingPlatform::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

/// <summary>
/// Returns the shapes position
/// </summary>
/// <returns></returns>
sf::Vector2f MovingPlatform::getPos()
{
	return m_shape.getPosition();
}

/// <summary>
/// Returns half the shapes size
/// </summary>
/// <returns></returns>
sf::Vector2f MovingPlatform::getHalfSize()
{
	return m_shape.getSize() / 2.0f;
}

/// <summary>
/// Returns the shape
/// </summary>
/// <returns></returns>
sf::RectangleShape MovingPlatform::getShape()
{
	return m_shape;
}
