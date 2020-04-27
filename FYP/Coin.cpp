#include "Coin.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="position"></param>
Coin::Coin(sf::Vector2f position)
{
	m_texture.loadFromFile("./Resources/Sprites/MarioCoin.png");

	m_shape.setPosition(position);
	m_shape.setSize(sf::Vector2f(32, 32));
	m_shape.setTexture(&m_texture);
	m_shape.setOrigin(m_shape.getSize() / 2.0f);
	animation = new Animation(&m_texture, sf::Vector2u(4,1), 0.3);
	m_alive = true;
}

/// <summary>
/// Deconstructor
/// </summary>
Coin::~Coin()
{
}

/// <summary>
/// Update Animation
/// </summary>
/// <param name="dt"></param>
void Coin::update(float dt)
{
	if (m_alive)
	{
		animation->update(0, dt, true);
		m_shape.setTextureRect(animation->m_uvRect);
	}
}

/// <summary>
/// Render the shape
/// </summary>
/// <param name="window"></param>
void Coin::draw(sf::RenderWindow& window)
{
	if (m_alive)
	{
		window.draw(m_shape);
	}
}

/// <summary>
/// Returns the coins rectangle shape
/// </summary>
/// <returns></returns>
sf::RectangleShape Coin::getShape()
{
	return m_shape;
}

bool Coin::getAlive()
{
	return m_alive;
}

sf::Vector2f Coin::getPos()
{
	return m_shape.getPosition();
}

/// <summary>
/// Deactivates coin
/// </summary>
void Coin::kill()
{
	m_alive = false;
}

/// <summary>
/// Sets the coins position to the passed vector
/// </summary>
/// <param name="pos"></param>
void Coin::setPos(sf::Vector2f pos)
{
	m_shape.setPosition(pos);
}

void Coin::setSize(sf::Vector2f size)
{
	m_shape.setSize(size);
}
