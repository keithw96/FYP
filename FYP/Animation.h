#pragma once

#include <SFML/Graphics.hpp> 
class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();

	void update(int row, float deltaTime, bool faceRight);

	sf::IntRect m_uvRect;

private:
	sf::Vector2u m_imageCount;
	sf::Vector2u m_currentImage;

	float m_totalTime;
	float m_switchTime;

};

