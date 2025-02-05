#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <istream>

#include "Player.h"
#include "Coin.h"
#include "Gamestates.h"
#include "Goal.h"
#include "Enemy.h"
#include "Pipe.h"
#include "Tile.h"
#include "MovingPlatform.h"
#include "QuestionBlock.h"

enum class PlayState
{
	GAME,
	LOADING,
	GAMEOVER
};

class Play
{
public:

	Play();
	~Play();

	void init();

	void initLevel();
	void initNonTileMapEntities();
	void initBonusArea(int lvNum);
	void pollEvent(sf::Event& event, sf::RenderWindow& window, GameStates& m_currentGamestate);
	void update(float dt, GameStates& gameState, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void setView(sf::RenderWindow &window);
	void loadNextLevel();
	void killEverything();
private:

	PlayState m_currentPlayState;

	int m_currentWorld;
	int m_currentZone;
	int m_lives;
	int m_score;
	int m_coinCount;

	bool m_bonusRound;
	bool m_overWorld;
	bool m_underWorld;
	bool m_castle;

	sf::RectangleShape m_background;
	sf::RectangleShape m_renderRectangle;
	sf::RectangleShape m_updateRectangle;

	sf::Texture m_bgTexture;

	sf::Font m_font;

	sf::Text m_scoreTxt;
	sf::Text m_noCoinsTxt;
	Coin* m_coinTxt;
	sf::Text m_worldTxt;
	sf::Text m_timeTxt;
	sf::Text m_livesTxt;
	sf::Text m_gameOver;

	sf::Sprite m_livesSprite;
	sf::Texture m_livesTexture;

	sf::SoundBuffer m_bgMusicBuffer;
	sf::SoundBuffer m_deathSoundBuffer;

	sf::Sound m_bgMusic;
	sf::Sound m_deathSound;

	int m_timeLeft;
	sf::Clock m_timer;

	Player* m_player;
	Goal* m_goal;
	sf::View m_view;

	std::vector<Tile*> m_tiles;
	std::vector<Coin*> m_coins;
	std::vector<Enemy*> m_enemies;
	std::vector<Pipe*> m_pipes;
	std::vector<MovingPlatform*> m_movingPlatforms;
	std::vector<QuestionBlock*> m_questionBlocks;
	std::vector<sf::Sprite*> m_sprites;
	std::vector<sf::Texture*> m_textures;
};