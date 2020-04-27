#include "Enemy.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="path"></param>
Enemy::Enemy(std::string path, sf::Vector2f pos, int leftDestination, int rightDestination)
{
	if (!m_texture.loadFromFile(path))
	{
		std::cout << "could not load enemy" << std::endl;
	}

	m_shape.setPosition(pos);
	m_shape.setSize(sf::Vector2f(32, 32));
	m_shape.setTexture(&m_texture);
	m_shape.setOrigin(m_shape.getSize() / 2.0f);

	m_animation = new Animation(&m_texture, sf::Vector2u(2, 1), 0.7f);

	m_leftDestination = leftDestination;
	m_rightDestination = rightDestination;

	m_faceRight = true;
	m_moveRight = false;
	m_alive = true;

	m_row = 0;
	m_speed = -2;
}

/// <summary>
/// Deconstructor
/// </summary>
/// <returns></returns>
Enemy::~Enemy()
{
}

/// <summary>
/// Update Enemy Movement and animation
/// </summary>
/// <param name="dt"></param>
void Enemy::update(float dt)
{
	if (m_shape.getPosition().x > m_rightDestination && m_moveRight)
	{
		m_moveRight = false;
		m_speed *= -1;
	}
	else if (m_shape.getPosition().x < m_leftDestination && !m_moveRight)
	{
		m_moveRight = true;
		m_speed *= -1;
	}
	
	m_shape.move(sf::Vector2f(m_speed, 0));

	m_animation->update(m_row, dt, m_faceRight);
	m_shape.setTextureRect(m_animation->m_uvRect);
}

/// <summary>
/// Render Enemy
/// </summary>
/// <param name="window"></param>
void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

/// <summary>
/// Set m_alive to false so the enemy cannot be rendered, updated and can be removed from memory
/// </summary>
void Enemy::kill()
{
	m_alive = false;
}

/// <summary>
/// Returns the enemy's position
/// </summary>
/// <returns></returns>
sf::Vector2f Enemy::getPos()
{
	return m_shape.getPosition();
}

/// <summary>
/// Returns the Enemy's size divided by 2
/// </summary>
/// <returns></returns>
sf::Vector2f Enemy::getHalfSize()
{
	return m_shape.getSize() / 2.0f;
}

/// <summary>
/// Returns the enemy's rectangle shape
/// </summary>
/// <returns></returns>
sf::RectangleShape Enemy::getShape()
{
	return m_shape;
}

/// <summary>
/// Returns the enemy's alive boolean
/// </summary>
/// <returns></returns>
bool Enemy::getAlive()
{
	return m_alive;
}
