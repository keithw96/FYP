#include "QuestionBlock.h"

/// <summary>
/// Constructor
/// Block has a 5 percent chance of spawning with a 1up
/// </summary>
/// <param name="filePath"></param>
/// <param name="spentPath"></param>
/// <param name="pos"></param>
QuestionBlock::QuestionBlock(std::string filePath, std::string spentPath, sf::Vector2f pos)
{
	if (!m_texture.loadFromFile(filePath))
	{
		std::cout << "Failed to load QuestionBlock sprite" << std::endl;
	}
	if (!m_spentTexture.loadFromFile(spentPath))
	{
		std::cout << "Failed to load SpentQuestionBlock sprite" << std::endl;
	}
	m_shape.setTexture(&m_texture);
	m_shape.setSize(sf::Vector2f(32, 32));
	m_shape.setPosition(sf::Vector2f(pos));
	m_shape.setOrigin(m_shape.getSize() / 2.0f);

	m_spent = false;
}

/// <summary>
/// Deconstructor
/// </summary>
QuestionBlock::~QuestionBlock()
{
}

/// <summary>
/// Render the shape to the window
/// </summary>
/// <param name="window"></param>
void QuestionBlock::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

/// <summary>
/// If hit from the bottom change the texture set to spent to pervent multiple hits
/// </summary>
void QuestionBlock::hit()
{
	m_spent = true;
	m_shape.setTexture(&m_spentTexture);
}

/// <summary>
/// Returns the shape
/// </summary>
/// <returns></returns>
sf::RectangleShape QuestionBlock::getShape()
{
	return m_shape;
}

/// <summary>
/// Returns the shape's half size
/// </summary>
/// <returns></returns>
sf::Vector2f QuestionBlock::getHalfSize()
{
	return m_shape.getSize() / 2.0f;
}

/// <summary>
/// Returns the shapes position
/// </summary>
/// <returns></returns>
sf::Vector2f QuestionBlock::getPos()
{
	return m_shape.getPosition();
}

/// <summary>
/// Returns the m_spent boolean
/// </summary>
/// <returns></returns>
bool QuestionBlock::getSpent()
{
	return m_spent;
}
