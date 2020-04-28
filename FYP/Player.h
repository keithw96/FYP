#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Animation.h"
#include "Coin.h"
#include "Goal.h"
#include "Enemy.h"
#include "Pipe.h"
#include "Tile.h"
#include "MovingPlatform.h"
#include "QuestionBlock.h"
//#include "Gamestates.h"
class Player
{
public: 

	Player(sf::Vector2f pos);
	~Player();

	void init(sf::Vector2f pos);
	void update(float dt, std::vector<Tile*> tiles, std::vector<Coin*> coins, std::vector<Enemy*> enemies, std::vector<Pipe*> pipes, std::vector<MovingPlatform*> movingPlatforms,
				std::vector<QuestionBlock*> questionBlocks, Goal* goal, int& score, int& coinCount, sf::RectangleShape& renderRectangle);
	void draw(sf::RenderWindow& window);
	
	void PlatformCollision(std::vector<Tile*> platforms, sf::RectangleShape& renderRectangle);
	void coinCollision(std::vector<Coin*> coins, int& score, int& coinCount);
	void enemyCollision(std::vector<Enemy*> enemies, int& score, sf::RectangleShape& renderRectangle);
	void pipeCollision(std::vector<Pipe*> pipes, sf::RectangleShape& renderRectangle);
	void movingPlatformCollision(std::vector<MovingPlatform*> movingPlatforms, sf::RectangleShape& renderRectangle);
	void questionBlockCollision(std::vector<QuestionBlock*> questionBlocks, int& score, int& coinCount, sf::RectangleShape& renderRectangle);

	sf::Vector2f getPosition();
	sf::Vector2f getHalfSize();
	sf::RectangleShape getShape();
	bool getAlive();
private:

	Animation* m_animation;
	
	sf::SoundBuffer m_jumpBuffer;
	sf::SoundBuffer m_coinBuffer;
	sf::SoundBuffer m_stompBuffer;
	sf::SoundBuffer m_1upBuffer;

	sf::Sound m_coinSound;
	sf::Sound m_jumpSound;
	sf::Sound m_stompSound;
	sf::Sound m_1upSound;

	sf::Vector2f m_velocity;
	sf::Vector2f m_direction;

	sf::RectangleShape m_shape;
	sf::Texture m_texture;

	bool m_canJump;
	bool m_doubleJump;
	bool m_alive;
	bool m_faceRight;

	float m_jumpAccelaration;
	float m_gravity;
	float m_speed;

	int m_jumpCount;
	int m_row;
	int m_deathHeight;

};

