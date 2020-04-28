#pragma once
#include "Gamestates.h"
#include "Play.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class MainMenuScene
{
public:
	MainMenuScene();
	~MainMenuScene();

	void pollEvent(sf::Event event, sf::RenderWindow& window, GameStates &gameState, Play* play);
	void update(GameStates& gameState, sf::RenderWindow& window, Play* play);
	void render(sf::RenderWindow& window);

private:

	sf::Sprite m_background;
	sf::Sprite m_playBtn;
	sf::Texture m_backgroundTexture;
	sf::Texture m_playBtnTexture;
	sf::Texture m_playBtnSelectedTexture;
	sf::View m_view;
};

