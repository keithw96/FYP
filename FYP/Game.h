#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "MainMenuScene.h"

#include "Player.h"
#include "Gamestates.h"
#include "Play.h"
class Game
{
public:
	Game();
	~Game();

	void init();
	void pollEvent();
	void update();
	void draw();

private:

	MainMenuScene* m_mainMenuScene;

	Player* m_player;
	Play* m_playScene;
	sf::RenderWindow m_window;
	sf::View m_view;

	GameStates m_currentGameState;
};

