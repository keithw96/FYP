#include "MainMenuScene.h"

/// <summary>
/// Constructor
/// </summary>
MainMenuScene::MainMenuScene()
{
	if (!m_backgroundTexture.loadFromFile("./Resources/Sprites/MainMenuBackground.png"))
	{
		std::cout << "Failed to load main menu background texture";
	}

	if (!m_playBtnTexture.loadFromFile("./Resources/Sprites/PlayBtn.png"))
	{
		std::cout << "Failed to load play btn texture";
	}
	m_playBtn.setTexture(m_playBtnTexture);
	m_playBtn.setPosition(sf::Vector2f(750,650));

	if (!m_playBtnSelectedTexture.loadFromFile("./Resources/Sprites/PlayBtnSelected.png"))
	{
		std::cout << "Failed to load play btn selected texture";
	}
	m_background.setTexture(m_backgroundTexture);
	m_background.setPosition(sf::Vector2f(0, 0));

	m_view = sf::View();
	m_view.setSize(sf::Vector2f(1920, 1080));
	m_view.setCenter(sf::Vector2f(960, 540));
}

/// <summary>
/// Deconstructor
/// </summary>
MainMenuScene::~MainMenuScene()
{
}

/// <summary>
/// Event Listener
/// </summary>
/// <param name="event"></param>
/// <param name="window"></param>
/// <param name="gameState"></param>
/// <param name="play"></param>
void MainMenuScene::pollEvent(sf::Event event, sf::RenderWindow& window, GameStates& gameState, Play* play)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	default:
		break;
	}
}

/// <summary>
/// Main Menu update
/// Go to the play scene if the play button is clicked
/// </summary>
/// <param name="gameState"></param>
/// <param name="window"></param>
/// <param name="play"></param>
void MainMenuScene::update(GameStates& gameState, sf::RenderWindow& window, Play* play)
{
	if (m_playBtn.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
	{
		m_playBtn.setTexture(m_playBtnSelectedTexture);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			play->init();
			gameState = GameStates::LevelOne;
		}
	}
	else
	{
		m_playBtn.setTexture(m_playBtnTexture);
	}
}

/// <summary>
/// Render main menu
/// </summary>
/// <param name="window"></param>
void MainMenuScene::render(sf::RenderWindow& window)
{
	window.setView(m_view);
	window.draw(m_background);
	window.draw(m_playBtn);
}
