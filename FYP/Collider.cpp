#include "Collider.h"

Collider::Collider(sf::RectangleShape sprite):
	m_sprite(sprite)
{

}

Collider::~Collider()
{
}

void Collider::move(float dx, float dy)
{
	m_sprite.move(dx, dy);
}

bool Collider::CheckCollision(Collider& other, float push)
{
	std::cout << push << std::endl;

	sf::Vector2f otherPosition = other.getPosition();
	sf::Vector2f otherHalfSize = other.getHalfSize();
	sf::Vector2f thisPosition = getPosition();
	sf::Vector2f thisHalfSize = getHalfSize();

	/*std::cout << "Other: " << otherPosition.x << ", " << otherPosition.y << std::endl;
	std::cout << "this: " << thisPosition.x << ", " << thisPosition.y << std::endl;*/

	//std::cout << "Other: " << otherHalfSize.x << ", " << otherHalfSize.y << std::endl;
	//std::cout << "this: " << thisHalfSize.x << ", " << thisHalfSize.y << std::endl;

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float interSectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float interSectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (interSectX < 0.0f && interSectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (interSectX > interSectY)
		{
			if (deltaX > 0.0f)
			{
				move(interSectX * (1.0f - push), 0.0f);
				other.move(-interSectX * push, 0);
			}
			else
			{
				move(-interSectX * (1.0f - push), 0.0f);
				other.move(interSectX * push, 0);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				move(0.0f, interSectY * (1.0f - push));
				other.move(0.0f, -interSectY * push);
			}
			else
			{
				move(0.0f, -interSectY * (1.0f - push));
				other.move(0.0f, interSectY * push);
			}
		}

		return true;
	}

	return false;
}

sf::Vector2f Collider::getPosition()
{
	return m_sprite.getPosition();
}

sf::Vector2f Collider::getHalfSize()
{	
	return m_sprite.getSize() / 2.0f;
}
