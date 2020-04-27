#pragma once
#include "Gamestates.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class MainMenuScene
{
public:
	MainMenuScene();
	~MainMenuScene();

	void pollEvent(sf::Event event, sf::RenderWindow& window, GameStates &gameState);
	void update(GameStates& gameState, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);

private:

	sf::Sprite m_background;
	sf::Sprite m_playBtn;
	sf::Texture m_backgroundTexture;
	sf::Texture m_playBtnTexture;
	sf::View m_view;
};

