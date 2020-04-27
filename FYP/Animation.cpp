#include "Animation.h"

/// <summary>
/// Constructor
/// Sets the texture rect sizem number of frames and time between frames
/// </summary>
/// <param name="texture"></param>
/// <param name="imageCount"></param>
/// <param name="switchTime"></param>
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->m_imageCount = imageCount;
	this->m_switchTime = switchTime;
	m_totalTime = 0.0f;
	m_currentImage.x = 0;

	m_uvRect.width = texture->getSize().x / float(imageCount.x);
	m_uvRect.height = texture->getSize().y / float(imageCount.y);
}

/// <summary>
/// Deconstructor
/// </summary>
Animation::~Animation()
{

}

/// <summary>
/// Loop through animation frames
/// </summary>
/// <param name="row"></param>
/// <param name="deltaTime"></param>
/// <param name="faceRight"></param>
void Animation::update(int row, float deltaTime, bool faceRight)
{
	m_currentImage.y = row;
	m_totalTime += deltaTime * 2;

	if (m_totalTime >= m_switchTime)
	{
		m_totalTime -= m_switchTime;
		m_currentImage.x++;

		if (m_currentImage.x >= m_imageCount.x)
		{
			m_currentImage.x = 0;

		}
	}

	m_uvRect.top = m_currentImage.y * m_uvRect.height;

	if (faceRight)
	{
		m_uvRect.left = m_currentImage.x * m_uvRect.width;
		m_uvRect.width = abs(m_uvRect.width);
	}
	else
	{
		m_uvRect.left = (m_currentImage.x + 1) * abs(m_uvRect.width);
		m_uvRect.width = -abs(m_uvRect.width);
	}
}
