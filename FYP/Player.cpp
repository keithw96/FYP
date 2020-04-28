#include "Player.h"

/// <summary>
/// Constructor
/// Initialise variables
/// </summary>
Player::Player(sf::Vector2f pos)
{
	init(pos);
}

/// <summary>
/// Deconstructor
/// </summary>
Player::~Player()
{
}

/// <summary>
/// Initialise the players variables, texture and sound effects
/// </summary>
/// <param name="pos"></param>
void Player::init(sf::Vector2f pos)
{
	if (!m_texture.loadFromFile("./Resources/Sprites/MarioSpriteSheet1.png"))
	{
		std::cout << "Failed to load player sprite" << std::endl;
	}

	if (!m_jumpBuffer.loadFromFile("./Resources/Sounds/Jump.wav"))
	{
		std::cout << "Error Loading Jump Sound" << std::endl;
	}
	m_jumpSound.setBuffer(m_jumpBuffer);
	m_jumpSound.setVolume(30.0f);

	if (!m_coinBuffer.loadFromFile("./Resources/Sounds/Coin.wav"))
	{
		std::cout << "Error Loading Jump Sound" << std::endl;
	}
	m_coinSound.setBuffer(m_coinBuffer);
	m_coinSound.setVolume(30.0f);

	if (!m_stompBuffer.loadFromFile("./Resources/Sounds/StompEnemy.wav"))
	{
		std::cout << "Error Loading stomp sound" << std::endl;
	}
	m_stompSound.setBuffer(m_stompBuffer);
	

	m_animation = new Animation(&m_texture, sf::Vector2u(3, 3), 0.2f);

	m_shape.setPosition(pos);
	m_shape.setSize(sf::Vector2f(32, 32));
	m_shape.setTexture(&m_texture);
	m_shape.setOrigin(m_shape.getSize() / 2.0f);

	m_faceRight = true;
	m_canJump = false;
	m_doubleJump = false;
	m_alive = true;
	m_jumpCount = 0;
	m_row = 0;
	m_jumpAccelaration = 12;
	m_speed = 5;
	m_gravity = 15;
	m_deathHeight = 544;
}

/// <summary>
/// Update Collisions animations and movement
/// </summary>
/// <param name="dt"></param>
/// <param name="platforms"></param>
/// <param name="coins"></param>
/// <param name="spikes"></param>
void Player::update(float dt, std::vector<Tile*> platforms, std::vector<Coin*> coins,std::vector<Enemy*> enemies, std::vector<Pipe*> pipes, std::vector<MovingPlatform*> movingPlatforms , Goal *goal, int &score, int& coinCount)
{
	if (m_alive)
	{
		m_velocity.x = 0.0f;
		
		std::cout << m_shape.getPosition().x << ", " << m_shape.getPosition().y << std::endl;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && m_shape.getPosition().x > 0)
		{
			m_velocity.x -= m_speed;
			m_faceRight = false;

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			m_velocity.x += m_speed;
			m_faceRight = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_canJump)
		{
			m_jumpSound.play();
			m_canJump = false;
			m_velocity.y -= m_jumpAccelaration;
		}

		m_velocity.y += m_gravity * dt;

		if (m_velocity.x == 0.0f && m_canJump)
		{
			m_row = 0;
		}
		else if (!m_canJump)
		{
			m_row = 2;		
		}
		else if (m_velocity.x > 0.0f || m_velocity.x < 0.0f && m_canJump)
		{
			m_row = 1;
		}

		m_animation->update(m_row, dt, m_faceRight);
		m_shape.setTextureRect(m_animation->m_uvRect);

		m_shape.move(m_velocity);
		PlatformCollision(platforms);
		coinCollision(coins, score, coinCount);
		enemyCollision(enemies, score);
		pipeCollision(pipes);
		movingPlatformCollision(movingPlatforms);
		if (m_shape.getPosition().y > m_deathHeight)
		{
			m_alive = false;
		}
	}
}

/// <summary>
/// Render Player shape
/// </summary>
/// <param name="window"></param>
void Player::draw(sf::RenderWindow &window)
{
	if (m_alive)
	{
		window.draw(m_shape);
	}
}

/// <summary>
/// Detects collision with tiles using aab collision formula
/// 
/// dx - (halfSizeA + halfSizeB) = intersectX
/// dy - (halfSizeA + halfSizeB) = intersectY
/// 
/// If intersect is negative the rectangles are intersecting by intersect
/// The player is then moved by intersect to move it out of the tile
/// 
/// e.g. 
/// 
/// 7 - (5 + 5) = -3
/// 9 - (5 + 5) = -1
/// </summary>
/// <param name="tiles"></param>
void Player::PlatformCollision(std::vector<Tile*> tiles)
{
	for (auto t : tiles)
	{
		sf::Vector2f otherPosition = t->getPos();
		sf::Vector2f otherHalfSize = t->getHalfSize();
		sf::Vector2f thisPosition = getPosition();
		sf::Vector2f thisHalfSize = getHalfSize();
		
		//Distance between player and platform
		float deltaX = otherPosition.x - thisPosition.x;
		float deltaY = otherPosition.y - thisPosition.y;

							//Always make delta positive
		float interSectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
		float interSectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

		if (interSectX < 0.0f && interSectY < 0.0f)
		{
			if (interSectX > interSectY)
			{
				m_velocity.x = 0;
				if (deltaX > 0.0f)
				{
					m_shape.move(interSectX, 0.0f);
				}
				else
				{
					m_shape.move(-interSectX, 0.0f);
				}
			}
			else
			{
				m_velocity.y = 0;
				if (deltaY > 0.0f)
				{
					m_shape.move(0.0f, interSectY);

					m_canJump = true;
					m_jumpCount = 0;
				}
				else
				{
					m_shape.move(0.0f, -interSectY);
				}
			}
		}
	}
}

/// <summary>
/// Check for collision on coins and destroy them
/// </summary>
/// <param name="coins"></param>
void Player::coinCollision(std::vector<Coin*> coins, int &score, int& coinCount)
{
	for (auto c : coins)
	{
		if (m_shape.getGlobalBounds().intersects(c->getShape().getGlobalBounds()) && c->getAlive())
		{
			score += 200;
			coinCount += 1;
			m_coinSound.play();
			c->kill();
		}
	}
}

/// <summary>
/// Check for collision on the enemies.
/// Kill them if top collision is detected and kill the player if left right or bottom collision is detected
/// </summary>
/// <param name="enemies"></param>
void Player::enemyCollision(std::vector<Enemy*> enemies, int &score)
{
	for (auto e : enemies)
	{
		sf::Vector2f otherPosition = e->getPos();
		sf::Vector2f otherHalfSize = e->getHalfSize();
		sf::Vector2f thisPosition = getPosition();
		sf::Vector2f thisHalfSize = getHalfSize();

		float deltaX = otherPosition.x - thisPosition.x;
		float deltaY = otherPosition.y - thisPosition.y;

		float interSectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
		float interSectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

		if (interSectX < 0.0f && interSectY < 0.0f)
		{
			if (interSectX > interSectY)
			{
				m_velocity.x = 0;
				if (deltaX > 0.0f)
				{
					m_alive = false;
				}
				else
				{
					m_alive = false;
				}
			}
			else
			{
				if (deltaY > 0.0f)
				{
					m_velocity.y = 0;
					m_velocity.y -= m_jumpAccelaration * 0.66f;
					e->kill();
					m_stompSound.play();
					score += 100;
				}
				else
				{
					m_alive = false;
				}
			}
		}
	}
}

/// <summary>
/// Uses AABB collision to check for collision between the player and the moving platforms
/// </summary>
/// <param name="pipes"></param>
void Player::pipeCollision(std::vector<Pipe*> pipes)
{
	for (auto p : pipes)
	{
		sf::Vector2f otherPosition = p->getPos();
		sf::Vector2f otherHalfSize = p->getHalfSize();
		sf::Vector2f thisPosition = getPosition();
		sf::Vector2f thisHalfSize = getHalfSize();

		float deltaX = otherPosition.x - thisPosition.x;
		float deltaY = otherPosition.y - thisPosition.y;

		float interSectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
		float interSectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

		if (interSectX < 0.0f && interSectY < 0.0f)
		{
			if (interSectX > interSectY)
			{
				m_velocity.x = 0;
				if (deltaX > 0.0f)
				{
					m_shape.move(interSectX, 0.0f);
				}
				else
				{
					m_shape.move(-interSectX, 0.0f);
				}
			}
			else
			{
				m_velocity.y = 0;
				if (deltaY > 0.0f)
				{
					m_shape.move(0.0f, interSectY);

					m_canJump = true;
					m_jumpCount = 0;
				}
				else
				{
					m_shape.move(0.0f, -interSectY);
				}
			}
		}
	}
}

void Player::movingPlatformCollision(std::vector<MovingPlatform*> movingPlatforms)
{
	for (auto mp : movingPlatforms)
	{
		sf::Vector2f otherPosition = mp->getPos();
		sf::Vector2f otherHalfSize = mp->getHalfSize();
		sf::Vector2f thisPosition = getPosition();
		sf::Vector2f thisHalfSize = getHalfSize();

		float deltaX = otherPosition.x - thisPosition.x;
		float deltaY = otherPosition.y - thisPosition.y;

		float interSectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
		float interSectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

		if (interSectX < 0.0f && interSectY < 0.0f)
		{
			if (interSectX > interSectY)
			{
				m_velocity.x = 0;
				if (deltaX > 0.0f)
				{
					m_shape.move(interSectX, 0.0f);
				}
				else
				{
					m_shape.move(-interSectX, 0.0f);
				}
			}
			else
			{
				m_velocity.y = 0;
				if (deltaY > 0.0f)
				{
					m_shape.move(0.0f, interSectY);

					m_canJump = true;
					m_jumpCount = 0;
				}
				else
				{
					m_shape.move(0.0f, -interSectY * 10);
				}
			}
		}
	}
}

/// <summary>
/// Get the player shape's position
/// </summary>
/// <returns></returns>
sf::Vector2f Player::getPosition()
{
	return m_shape.getPosition();
}

/// <summary>
/// Get the player shape's halfsize
/// </summary>
/// <returns></returns>
sf::Vector2f Player::getHalfSize()
{
	return m_shape.getSize() / 2.0f;
}

/// <summary>
/// Get the players shape
/// </summary>
/// <returns></returns>
sf::RectangleShape Player::getShape()
{
	return m_shape;
}

/// <summary>
/// Returns the players alive boolean
/// </summary>
/// <returns></returns>
bool Player::getAlive()
{
	return m_alive;
}
