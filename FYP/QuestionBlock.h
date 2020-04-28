#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class QuestionBlock
{
public:

	QuestionBlock(std::string filePath, std::string spentPath, sf::Vector2f pos);
	~QuestionBlock();

	void draw(sf::RenderWindow& window);
	void hit();

	sf::RectangleShape getShape();
	sf::Vector2f getHalfSize();
	sf::Vector2f getPos();
	bool getHasCoin();
	bool getSpent();
private:

	sf::RectangleShape m_shape;
	sf::Texture m_texture;
	sf::Texture m_spentTexture;
	bool m_hasCoin;
	bool m_spent;
};

