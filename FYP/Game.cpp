#include "Game.h"

/// <summary>
/// Constructor
/// Initialises window
/// </summary>
Game::Game() : m_window(sf::VideoMode(1920, 1080), "FYP")
{
	init();
}

/// <summary>
/// Deconstructor
/// </summary>
Game::~Game()
{

}

/// <summary>
/// Initialiser function
/// Caps window framerate and creates game elements
/// </summary>
void Game::init()
{
	m_window.setFramerateLimit(30);
	
	m_mainMenuScene = new MainMenuScene();
	m_playScene = new Play();

	m_currentGameState = GameStates::MainMenu;
}

/// <summary>
/// Event Listener
/// </summary>
void Game::pollEvent()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		switch (m_currentGameState)
		{
		case GameStates::MainMenu:
			m_mainMenuScene->pollEvent(event, m_window, m_currentGameState, m_playScene);
			break;
		case GameStates::LevelOne:
			m_playScene->pollEvent(event, m_window, m_currentGameState);
			break;
	
		default:
			break;
		}
	}
}

/// <summary>
/// Game Loop
/// Update all game elements
/// </summary>
void Game::update()
{
	float deltaTime = 0.0f;
	sf::Clock clock;

	while (m_window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		pollEvent();

		switch (m_currentGameState)
		{
		case GameStates::MainMenu:
			m_mainMenuScene->update(m_currentGameState, m_window, m_playScene);
			break;
		case GameStates::LevelOne:
			m_playScene->update(deltaTime, m_currentGameState, m_window);
			break;
		default:
			break;
		}

		draw();
	}
}

/// <summary>
/// Render game elements
/// </summary>
void Game::draw()
{
	m_window.clear(sf::Color(150,150,150));

	switch (m_currentGameState)
	{
	case GameStates::MainMenu:
		m_mainMenuScene->render(m_window);
		break;
	case GameStates::LevelOne:
		m_playScene->render(m_window);
		break;
	default:
		break;
	}
	

	m_window.display();
}
