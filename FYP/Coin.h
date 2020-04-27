#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <iostream>
class Coin
{
public:

	Coin(sf::Vector2f position);
	~Coin();

	void update(float dt);
	void draw(sf::RenderWindow &window);
	sf::RectangleShape getShape();
	bool getAlive();
	sf::Vector2f getPos();
	void kill();
	void setPos(sf::Vector2f pos);
	void setSize(sf::Vector2f size);
private:
	Animation* animation;
	sf::RectangleShape m_shape;
	sf::Texture m_texture;
	bool m_alive; 

};

