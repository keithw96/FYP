#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
class Enemy
{
public:
	Enemy(std::string path, sf::Vector2f pos, int leftDestination, int rightDestination);
	~Enemy();

	void update(float dt);
	void draw(sf::RenderWindow& window);
	void kill();

	sf::Vector2f getPos();
	sf::Vector2f getHalfSize();
	sf::RectangleShape getShape();
	bool getAlive();
private:

	sf::RectangleShape m_shape;
	sf::Texture m_texture;

	int m_leftDestination;
	int m_rightDestination;

	Animation* m_animation;

	bool m_faceRight;
	bool m_moveUp;
	bool m_alive;

	float m_speed;

	int m_row;
};

