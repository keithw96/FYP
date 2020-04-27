#include "MainMenuScene.h"

MainMenuScene::MainMenuScene()
{
	if (!m_backgroundTexture.loadFromFile("./Resources/Sprites/MainMenuBackground.png"))
	{
		std::cout << "Failed to load main menu background texture";
	}

	m_background.setTexture(m_backgroundTexture);
	m_background.setPosition(sf::Vector2f(0, 0));
	m_view = sf::View();
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::pollEvent(sf::Event event, sf::RenderWindow& window, GameStates& gameState)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::KeyReleased:
		if (event.key.code == sf::Keyboard::Space)
		{
			gameState = GameStates::LevelOne;
		}
		break;
	default:
		break;
	}
}

void MainMenuScene::update(GameStates& gameState, sf::RenderWindow& window)
{
	/*sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
 				gameState = GameStates::LevelOne;
			}
		}
	}*/
}

void MainMenuScene::render(sf::RenderWindow& window)
{
	window.setView(m_view);
	window.draw(m_background);
}
