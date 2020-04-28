#include "Play.h"

/// <summary>
/// Constructor
/// </summary>
Play::Play()
{
	init();
}

/// <summary>
/// Deconstructor
/// </summary>
Play::~Play()
{
}

/// <summary>
/// Initialise the play scene's variables, textures and sound files
/// </summary>
void Play::init()
{
	if (!m_deathSoundBuffer.loadFromFile("./Resources/Sounds/DeathSound.wav"))
	{
		std::cout << "could not load Death Sound" << std::endl;
	}
	if(!m_font.loadFromFile("./Resources/Font/prstart.ttf"))
	{
		std::cout << "could not load font" << std::endl;
	}

	m_scoreTxt.setFont(m_font);
	m_timeTxt.setFont(m_font);
	m_worldTxt.setFont(m_font);
	m_noCoinsTxt.setFont(m_font);

	m_deathSound.setBuffer(m_deathSoundBuffer);

	m_bonusRound = false;
	m_overWorld = true;
	m_underWorld = false;
	m_castle = false;
	m_currentWorld = 1;
	m_currentZone = 1;
	m_lives = 3;
	m_score = 0;
	m_coinCount = 0;

	m_scoreTxt.setFont(m_font);
	m_scoreTxt.setString("MARIO \n" + std::to_string(m_score));
	m_scoreTxt.setCharacterSize(12);

	m_timeTxt.setFont(m_font);
	m_timeTxt.setString("Time \n");
	m_scoreTxt.setCharacterSize(12);

	m_worldTxt.setFont(m_font);
	m_worldTxt.setString("WORLD \n" + std::to_string(m_currentWorld) + "-" + std::to_string(m_currentZone));
	m_worldTxt.setCharacterSize(12);

	m_livesTexture.loadFromFile("./Resources/Sprites/LivesSprite.png");
	m_livesSprite.setTexture(m_livesTexture);
	m_livesTxt.setFont(m_font);
	m_livesTxt.setString("x" + std::to_string(m_lives));
	m_livesTxt.setCharacterSize(12);

	m_noCoinsTxt.setFont(m_font);
	m_noCoinsTxt.setString("x" );
	m_noCoinsTxt.setCharacterSize(12);
	m_coinTxt = new Coin(sf::Vector2f(0, 0));
	m_coinTxt->setSize(sf::Vector2f(16, 16));

	initLevel();
}

/// <summary>
/// Initialise the tile map, sound files, textures and variables
/// </summary>
void Play::initLevel()
{
	m_view = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(910.0f, 512.0f));

	std::string enemyPath;

	m_renderRectangle.setPosition(m_view.getCenter());
	m_renderRectangle.setSize(m_view.getSize());

	if (m_overWorld)
	{
		m_background.setFillColor(sf::Color(135, 206, 235, 255));

		if (!m_bgMusicBuffer.loadFromFile("./Resources/Sounds/OverworldTheme.wav"))
		{
			std::cout << "Error Loading Jump Sound" << std::endl;
		}
		enemyPath = "./Resources/Sprites/OverworldGoomba.png";
	}
	else if (m_underWorld)
	{
		if (!m_bgMusicBuffer.loadFromFile("./Resources/Sounds/UndergroundTheme.wav"))
		{
			std::cout << "Error Loading Jump Sound" << std::endl;
		}
		m_background.setFillColor(sf::Color::Black);
		enemyPath = "./Resources/Sprites/UnderworldGoomba.png";
	}
	else if (m_castle)
	{
		if (!m_bgMusicBuffer.loadFromFile("./Resources/Sounds/CastleTheme.wav"))
		{
			std::cout << "Error Loading Jump Sound" << std::endl;
		}
		m_background.setFillColor(sf::Color::Black);
		enemyPath = "./Resources/Sprites/CastleGoomba.png";
	}
	m_bgMusic.setBuffer(m_bgMusicBuffer);
	m_bgMusic.setLoop(true);
	m_bgMusic.play();

	m_background.setPosition(sf::Vector2f(0.0f, -16.0f));
	m_background.setSize(sf::Vector2f(6688, 512));
	std::string line;
	std::ifstream myFile("./Resources/Maps/Level" + std::to_string(m_currentWorld) + "-" + std::to_string(m_currentZone) + ".txt");
	std::vector<int> mapArray;

	if (myFile.is_open())
	{
		while (getline(myFile, line, ','))
		{
			mapArray.push_back(std::stoi(line));
		}
		myFile.close();
	}

	int arrayIndex = 0;

	for (int j = 0; j < 15; j++)
	{
		for (int i = 0; i < 209; i++)
		{
			if (mapArray[arrayIndex] == 1)
			{
				Tile* platform = new Tile("./Resources/Sprites/Ground.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 2)
			{
				Tile* platform = new Tile("./Resources/Sprites/Platform.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 3)
			{
				Tile* platform = new Tile("./Resources/Sprites/OverworldSpentBlock.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 4)
			{
				Tile* platform = new Tile("./Resources/Sprites/StaircaseBlock.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 5)
			{
				QuestionBlock* questionBlock = new QuestionBlock("./Resources/Sprites/OverworldQuestionBlock.png", "./Resources/Sprites/OverworldSpentBlock.png", sf::Vector2f(32 * i, 32 * j));
				m_questionBlocks.push_back(questionBlock);
				
			}
			else if (mapArray[arrayIndex] == 6)
			{
				//m_player = new Player(sf::Vector2f(3297, 288));
				m_player = new Player(sf::Vector2f(32 * i, 32 * j));
			}
			else if (mapArray[arrayIndex] == 7)
			{
				Tile* platform = new Tile("./Resources/Sprites/UndergroundStaircaseBlock.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 9)
			{
				QuestionBlock* questionBlock = new QuestionBlock("./Resources/Sprites/UndergroundQuestionBlock.png", "./Resources/Sprites/UndergroundSpentBlock.png", sf::Vector2f(32 * i, 32 * j));
				m_questionBlocks.push_back(questionBlock);
		
			}
			else if (mapArray[arrayIndex] == 10)
			{
				Tile* platform = new Tile("./Resources/Sprites/UndergroundPlatformBlock.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 11)
			{
				Tile* platform = new Tile("./Resources/Sprites/UndergroundGroundBlock.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 12)
			{
				Coin* coin = new Coin(sf::Vector2f(32 * i, 32 * j));
				m_coins.push_back(coin);
			}
			else if (mapArray[arrayIndex] == 13)
			{
				Tile* platform = new Tile("./Resources/Sprites/PipeVertical.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 14)
			{
				sf::Texture* tex = new sf::Texture;
				sf::Sprite* sprite = new sf::Sprite;
				tex->loadFromFile("./Resources/Sprites/TreeTrunk.png");
				sprite->setTexture(*tex);
				m_textures.push_back(tex);
				sprite->setPosition(sf::Vector2f(32 * i, 32 * j));
				sprite->setOrigin(16, 16);
				m_sprites.push_back(sprite);
			}
			else if (mapArray[arrayIndex] == 15)
			{
				Tile* platform = new Tile("./Resources/Sprites/TreeTop.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 16)
			{
				Tile* platform = new Tile("./Resources/Sprites/CastleTile.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 17)
			{
				Tile* platform = new Tile("./Resources/Sprites/CastleBridge.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 18)
			{
				Tile* platform = new Tile("./Resources/Sprites/CastleSpentBlock.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 19)
			{
				sf::Texture* tex = new sf::Texture;
				sf::Sprite* sprite = new sf::Sprite;
				tex->loadFromFile("./Resources/Sprites/LavaTop.png");
				sprite->setTexture(*tex);
				m_textures.push_back(tex);
				sprite->setPosition(sf::Vector2f(32 * i, 32 * j));
				sprite->setOrigin(sprite->getTextureRect().width / 2, sprite->getTextureRect().height / 2);
				m_sprites.push_back(sprite);
			}
			else if (mapArray[arrayIndex] == 20)
			{	
				sf::Texture* tex = new sf::Texture;
				sf::Sprite* sprite = new sf::Sprite;
				tex->loadFromFile("./Resources/Sprites/Lava.png");
				sprite->setTexture(*tex);
				m_textures.push_back(tex);
				sprite->setPosition(sf::Vector2f(32 * i, 32 * j));
				sprite->setOrigin(sprite->getTextureRect().width / 2, sprite->getTextureRect().height / 2);
				m_sprites.push_back(sprite);

			}
			else if (mapArray[arrayIndex] == 21)
			{
				m_goal = new Goal("./Resources/Sprites/Flag.png", sf::Vector2f(32, 288), sf::Vector2f(32 * i, 32 * j));
			}
			else if (mapArray[arrayIndex] == 22)
			{
				m_goal = new Goal("./Resources/Sprites/PipeGoal.png", sf::Vector2f(64, 64), sf::Vector2f(32 * i, 32 * j - 16));
			}
			else if (mapArray[arrayIndex] == 23)
			{
				sf::Texture* tex = new sf::Texture;
				sf::Sprite* sprite = new sf::Sprite;
				tex->loadFromFile("./Resources/Sprites/SingleCloud.png");
				sprite->setTexture(*tex);
				m_textures.push_back(tex);
				sprite->setPosition(sf::Vector2f(32 * i, 32 * j));
				sprite->setOrigin(sprite->getTextureRect().width / 2, sprite->getTextureRect().height / 2);
				m_sprites.push_back(sprite);
			}
			else if (mapArray[arrayIndex] == 24)
			{
				sf::Texture* tex = new sf::Texture;
				sf::Sprite* sprite = new sf::Sprite;
				tex->loadFromFile("./Resources/Sprites/DoubleCloud.png");
				sprite->setTexture(*tex);
				m_textures.push_back(tex);
				sprite->setPosition(sf::Vector2f(32 * i, 32 * j));
				sprite->setOrigin(sprite->getTextureRect().width / 2, sprite->getTextureRect().height / 2);
				m_sprites.push_back(sprite);
			}
			else if (mapArray[arrayIndex] == 25)
			{
				sf::Texture* tex = new sf::Texture;
				sf::Sprite* sprite = new sf::Sprite;
				tex->loadFromFile("./Resources/Sprites/TripleCloud.png");
				sprite->setTexture(*tex);
				m_textures.push_back(tex);
				sprite->setPosition(sf::Vector2f(32 * i, 32 * j));
				sprite->setOrigin(sprite->getTextureRect().width / 2, sprite->getTextureRect().height / 2);
				m_sprites.push_back(sprite);
			}
			arrayIndex++;
		}
	}
	initNonTileMapEntities();
}


void Play::initBonusArea(int lvNum)
{
	m_view = sf::View(sf::Vector2f(240.0f, 192.0f), sf::Vector2f(512.0f, 384.0f));
	m_renderRectangle.setPosition(m_view.getCenter());
	m_renderRectangle.setSize(m_view.getSize());
	m_renderRectangle.setFillColor(sf::Color::Green);
	if (!m_bgMusicBuffer.loadFromFile("./Resources/Sounds/UndergroundTheme.wav"))
	{
		std::cout << "Error Loading Jump Sound" << std::endl;
	}
	m_bgMusic.setBuffer(m_bgMusicBuffer);
	m_bgMusic.setLoop(true);
	m_bgMusic.play();

	m_background.setFillColor(sf::Color::Black);
	m_background.setPosition(sf::Vector2f(-16.0f, -24.0f));
	m_background.setSize(sf::Vector2f(512, 384));
	std::string line;
	std::ifstream myFile("./Resources/Maps/BonusArea" + std::to_string(lvNum) + ".txt");
	std::vector<int> mapArray;

	if (myFile.is_open())
	{
		while (getline(myFile, line, ',') && line != "end")
		{
			mapArray.push_back(std::stoi(line));
		}
		myFile.close();
	}

	int arrayIndex = 0;

	for (int j = 0; j < 12; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			if (mapArray[arrayIndex] == 6)
			{
				m_player = new Player(sf::Vector2f(32 * i, 32 * j));
			}
			else if (mapArray[arrayIndex] == 10)
			{
				Tile* platform = new Tile("./Resources/Sprites/UndergroundPlatformBlock.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 11)
			{
				Tile* platform = new Tile("./Resources/Sprites/UndergroundGroundBlock.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 12)
			{
				Coin* coin = new Coin(sf::Vector2f(32 * i, 32 * j));
				m_coins.push_back(coin);
			}
			else if (mapArray[arrayIndex] == 13)
			{
				Tile* platform = new Tile("./Resources/Sprites/PipeVertical.png", sf::Vector2f(32 * i, 32 * j));
				m_tiles.push_back(platform);
			}
			else if (mapArray[arrayIndex] == 22)
			{
				m_goal = new Goal("./Resources/Sprites/PipeGoal.png", sf::Vector2f(64, 64), sf::Vector2f(32 * i, 32 * j - 16));
			}
			arrayIndex++;
		}
	}
}

/// <summary>
/// Event Listener
/// </summary>
/// <param name="event"></param>
/// <param name="window"></param>
void Play::pollEvent(sf::Event& event, sf::RenderWindow& window)
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
/// Update all of the elements in the game
/// </summary>
/// <param name="dt"></param>
/// <param name="gameState"></param>
/// <param name="window"></param>
void Play::update(float dt, GameStates& gameState, sf::RenderWindow& window)
{
	m_player->update(dt, m_tiles, m_coins, m_enemies, m_pipes, m_movingPlatforms, m_questionBlocks, m_goal, m_score, m_coinCount, m_lives, m_renderRectangle);
	m_coinTxt->update(dt);
	if (!m_player->getAlive())
	{
		m_bgMusic.stop();
		m_deathSound.play();
		killEverything();
		initLevel();
		m_lives--;
	}

	if (m_lives <= 0)
	{
		window.close();
	}

	if (m_coinCount == 50)
	{
		m_coinCount -= 50;
		m_lives++;
	}

	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->update(dt);
		if (!m_coins[i]->getAlive())
		{
			m_coins[i]->~Coin();
			m_coins[i] = nullptr;
			m_coins.erase(m_coins.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->update(dt);
		if (!m_enemies[i]->getAlive())
		{
			m_enemies[i]->~Enemy();
			m_enemies[i] = nullptr;
			m_enemies.erase(m_enemies.begin() + i);
			i--;
		}
	}

	for (auto mp : m_movingPlatforms)
	{
		mp->update();
	}

	if (m_player->getShape().getGlobalBounds().intersects(m_goal->getShape().getGlobalBounds()))
	{

		if (!m_bonusRound)
		{
			m_score += 5000;
			int bonus = rand() % 5 + 1;
			m_bonusRound = true;
			killEverything();
			initBonusArea(bonus);
		}
		else
		{
			m_bonusRound = false;
			if (m_currentZone < 4)
			{
				m_currentZone++;
			}
			else
			{
				m_currentWorld++;
				m_currentZone = 1;
			}
			killEverything();
			loadNextLevel();
		}
	}

	
	m_renderRectangle.setPosition(m_view.getCenter().x - (m_view.getSize().x) / 2, 0);
}

/// <summary>
/// Render all of the elements in the level
/// </summary>
/// <param name="window"></param>
void Play::render(sf::RenderWindow& window)
{
	if (!m_bonusRound)
	{
		setView();
	}
	window.setView(m_view);
	window.draw(m_background);

	for (auto s : m_sprites)
	{
		if (s->getGlobalBounds().intersects(m_renderRectangle.getGlobalBounds()))
		{
			window.draw(*s);
		}
	}

	m_player->draw(window);

	for (auto p : m_tiles)
	{
		if (p->getShape().getGlobalBounds().intersects(m_renderRectangle.getGlobalBounds()))
		{
			p->draw(window);
		}
	}
	for (auto c : m_coins)
	{
		if (c->getShape().getGlobalBounds().intersects(m_renderRectangle.getGlobalBounds()))
		{
			c->draw(window);
		}
	}
	
	for (auto q : m_questionBlocks)
	{
		if (q->getShape().getGlobalBounds().intersects(m_renderRectangle.getGlobalBounds()))
		{
			q->draw(window);
		}
	}

	for (auto e : m_enemies)
	{
		if (e->getShape().getGlobalBounds().intersects(m_renderRectangle.getGlobalBounds()))
		{
			e->draw(window);
		}
	}

	for (auto p : m_pipes)
	{
		if (p->getShape().getGlobalBounds().intersects(m_renderRectangle.getGlobalBounds()))
		{
			p->draw(window);
		}
	}

	for (auto mp : m_movingPlatforms)
	{
		if (mp->getShape().getGlobalBounds().intersects(m_renderRectangle.getGlobalBounds()))
		{
			mp->draw(window);
		}
	}

	m_goal->draw(window);

	m_worldTxt.setString(("WORLD \n " + std::to_string(m_currentWorld) + "-" + std::to_string(m_currentZone)));
	m_worldTxt.setPosition(sf::Vector2f(m_view.getCenter().x + (m_view.getSize().x * 0.1), m_view.getCenter().y - m_view.getSize().y * 0.49));
	window.draw(m_worldTxt);

	m_scoreTxt.setString("MARIO \n" + std::to_string(m_score));
	m_scoreTxt.setPosition(sf::Vector2f(m_view.getCenter().x - (m_view.getSize().x * 0.45), m_view.getCenter().y - m_view.getSize().y * 0.49));
	window.draw(m_scoreTxt);

	m_livesSprite.setPosition(sf::Vector2f(m_view.getCenter().x - (m_view.getSize().x * 0.25), m_view.getCenter().y - m_view.getSize().y * 0.49));
	m_livesTxt.setString("x" + std::to_string(m_lives));
	m_livesTxt.setPosition(sf::Vector2f(m_livesSprite.getPosition().x + 20, m_livesSprite.getPosition().y));
	window.draw(m_livesSprite);
	window.draw(m_livesTxt);


	m_coinTxt->setPos(sf::Vector2f(m_view.getCenter().x - (m_view.getSize().x * 0.1), m_view.getCenter().y - m_view.getSize().y * 0.45));
	m_noCoinsTxt.setPosition(sf::Vector2f(m_coinTxt->getPos().x + 10, m_coinTxt->getPos().y - 16));
	m_noCoinsTxt.setString("x" + std::to_string(m_coinCount));
	m_coinTxt->draw(window);
	window.draw(m_noCoinsTxt);
}

/// <summary>
/// Set the View to center on the player but not go past level boundary
/// </summary>
void Play::setView()
{
	sf::Vector2f playerpos = m_player->getPosition();
	sf::Vector2f viewCenter = m_view.getCenter();
	sf::Vector2f viewSize = m_view.getSize();

	if (playerpos.x - (viewSize.x / 2) < 0) //check to see if viewport  x will be less than 0 on x axis
	{
		viewCenter.x = viewSize.x / 2;
		m_view.setCenter(sf::Vector2f(viewCenter.x, 240));
	}
	else
	{
		m_view.setCenter(playerpos.x, 240);
	}

}
/// <summary>
/// Loads the next level
/// </summary>
void Play::loadNextLevel()
{
	if (m_currentWorld == 1 && m_currentZone == 2)
	{
		m_overWorld = false;
		m_underWorld = true;
		initLevel();
	}
	else if (m_currentWorld == 1 && m_currentZone == 3)
	{
		m_underWorld = false;
		m_overWorld = true;
		initLevel();
	}
	else if (m_currentWorld == 1 && m_currentZone == 4)
	{
		m_overWorld = false;
		m_castle = true;
		initLevel();
	}
}

/// <summary>
/// Remove everything from memory using dynamic memory deallocation
/// </summary>
void Play::killEverything()
{
	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->~Coin();
		m_coins[i] = nullptr;
		m_coins.erase(m_coins.begin() + i);
		i--;
	}
	for (int i = 0; i < m_tiles.size(); i++)
	{
		m_tiles[i]->~Tile();
		m_tiles[i] = nullptr;
		m_tiles.erase(m_tiles.begin() + i);
		i--;
	}
	for (int i = 0; i < m_textures.size(); i++)
	{
		m_textures[i] = nullptr;
		m_textures.erase(m_textures.begin() + i);
		i--;
	}
	for (int i = 0; i < m_sprites.size(); i++)
	{
		m_sprites[i] = nullptr;
		m_sprites.erase(m_sprites.begin() + i);
		i--;
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->~Enemy();
		m_enemies[i] = nullptr;
		m_enemies.erase(m_enemies.begin() + i);
		i--;
	}
	for (int i = 0; i < m_pipes.size(); i++)
	{
		m_pipes[i]->~Pipe();
		m_pipes[i] = nullptr;
		m_pipes.erase(m_pipes.begin() + i);
		i--;
	}
	for (int i = 0; i < m_movingPlatforms.size(); i++)
	{
		m_movingPlatforms[i]->~MovingPlatform();
		m_movingPlatforms[i] = nullptr;
		m_movingPlatforms.erase(m_movingPlatforms.begin() + i);
		i--;
	}

	for (int i = 0; i < m_questionBlocks.size(); i++)
	{
		m_questionBlocks[i]->~QuestionBlock();
		m_questionBlocks[i] = nullptr;
		m_questionBlocks.erase(m_questionBlocks.begin() + i);
		i--;
	}
	m_player = nullptr;
	m_goal = nullptr;
}

/// <summary>
/// Initialise all entities that are not apart of the tile map or have specific initialiser variables
/// </summary>
void Play::initNonTileMapEntities()
{
	if (m_currentWorld == 1 && m_currentZone == 1)
	{
		Enemy* enemy = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(680, 384), 18, 882);
		m_enemies.push_back(enemy);
		Enemy* enemy2 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(1330, 384), 1319, 1559);
		m_enemies.push_back(enemy2);
		Enemy* enemy3 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(1761, 384), 1666, 1872);
		m_enemies.push_back(enemy3);
		Enemy* enemy4 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(1826, 384), 1666, 1872);
		m_enemies.push_back(enemy4);
		Enemy* enemy5 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(2527, 256), 2492, 2562);
		m_enemies.push_back(enemy5);
		Enemy* enemy6 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(2645, 128), 2590, 2820);
		m_enemies.push_back(enemy6);
		Enemy* enemy7 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(3070, 384), 2915, 3325);
		m_enemies.push_back(enemy7);
		Enemy* enemy8 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(3135, 384), 2915, 3325);
		m_enemies.push_back(enemy8);
		Enemy* enemy9 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(3838, 384), 3714, 4190);
		m_enemies.push_back(enemy9);
		Enemy* enemy10 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(3886, 384), 3715, 4190);
		m_enemies.push_back(enemy10);
		Enemy* enemy11 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(3950, 384), 3715, 4190);
		m_enemies.push_back(enemy11);
		Enemy* enemy12 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(3998, 384), 3715, 4190);
		m_enemies.push_back(enemy12);
		Enemy* enemy13 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(5470, 384), 5135, 5614);
		m_enemies.push_back(enemy13);
		Enemy* enemy14 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(5518, 384), 5135, 5614);
		m_enemies.push_back(enemy14);

		Pipe* pipe = new Pipe("./Resources/Sprites/LevelPipe.png", sf::Vector2f(930, 370), sf::Vector2f(64, 64));
		m_pipes.push_back(pipe);
		Pipe* pipe2 = new Pipe("./Resources/Sprites/LevelPipe.png", sf::Vector2f(1270, 352), sf::Vector2f(64, 96));
		m_pipes.push_back(pipe2);
		Pipe* pipe3 = new Pipe("./Resources/Sprites/LevelPipe.png", sf::Vector2f(1608, 336), sf::Vector2f(64, 128));
		m_pipes.push_back(pipe3);
		Pipe* pipe4 = new Pipe("./Resources/Sprites/LevelPipe.png", sf::Vector2f(1920, 336), sf::Vector2f(64, 128));
		m_pipes.push_back(pipe4);
		Pipe* pipe5 = new Pipe("./Resources/Sprites/LevelPipe.png", sf::Vector2f(5087, 370), sf::Vector2f(64, 64));
		m_pipes.push_back(pipe5);
		Pipe* pipe6 = new Pipe("./Resources/Sprites/LevelPipe.png", sf::Vector2f(5662, 370), sf::Vector2f(64, 64));
		m_pipes.push_back(pipe6);
	}
	if (m_currentWorld == 1 && m_currentZone == 2)
	{
		Enemy* enemy = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(457, 384), 32, 544);
		m_enemies.push_back(enemy);
		Enemy* enemy2 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(507, 384), 32, 544);
		m_enemies.push_back(enemy2);
		Enemy* enemy3 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(958, 384), 928, 992);
		m_enemies.push_back(enemy3);
		Enemy* enemy4 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(1377, 384), 1187, 1537);
		m_enemies.push_back(enemy4);
		Enemy* enemy5 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(1472, 384), 1187, 1537);
		m_enemies.push_back(enemy5);
		Enemy* enemy6 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(1405, 192), 1345, 1440);
		m_enemies.push_back(enemy6);
		Enemy* enemy7 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(1919, 384), 1824, 2094);
		m_enemies.push_back(enemy7);
		Enemy* enemy8 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(1984, 384), 1824, 2094);
		m_enemies.push_back(enemy8);
		Enemy* enemy9 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(2367, 384), 2177, 2562);
		m_enemies.push_back(enemy9);
		Enemy* enemy10 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(2517, 256), 2467, 2562);
		m_enemies.push_back(enemy10);
		Enemy* enemy11 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(2850, 384), 2655, 3087);
		m_enemies.push_back(enemy11);															  
		Enemy* enemy12 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(2900, 384), 2655, 3087);
		m_enemies.push_back(enemy12);															  
		Enemy* enemy13 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(2960, 384), 2655, 3087);
		m_enemies.push_back(enemy13);
		Enemy* enemy14 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(3485, 384), 3405, 3566);
		m_enemies.push_back(enemy14);
		Enemy* enemy15 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(4131, 384), 4066, 4256);
		m_enemies.push_back(enemy15);
		Enemy* enemy16 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(4186, 384), 4066, 4256);
		m_enemies.push_back(enemy16);
		Enemy* enemy17 = new Enemy("./Resources/Sprites/UnderworldGoomba.png", sf::Vector2f(4811, 384), 4706, 4926);
		m_enemies.push_back(enemy17);

		Pipe* pipe = new Pipe("./Resources/Sprites/LevelPipe.png", sf::Vector2f(3614, 370), sf::Vector2f(64, 64));
		m_pipes.push_back(pipe);
		Pipe* pipe2 = new Pipe("./Resources/Sprites/LevelPipe.png", sf::Vector2f(3357, 336), sf::Vector2f(64, 128));
		m_pipes.push_back(pipe2);
		Pipe* pipe3 = new Pipe("./Resources/Sprites/LevelPipe.png", sf::Vector2f(3135, 352), sf::Vector2f(64, 96));
		m_pipes.push_back(pipe3);

		MovingPlatform* movingPlatform1 = new MovingPlatform(sf::Vector2f(4563, 5), 0, 450);
		m_movingPlatforms.push_back(movingPlatform1);
		MovingPlatform* movingPlatform2 = new MovingPlatform(sf::Vector2f(5060, 445), 0, 450);
		m_movingPlatforms.push_back(movingPlatform2);
	}
	if (m_currentWorld == 1 && m_currentZone == 3)
	{
		Enemy* enemy = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(937, 128), 867, 992);
		m_enemies.push_back(enemy);
		Enemy* enemy2 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(1412, 96), 1347, 1472);
		m_enemies.push_back(enemy2);
		Enemy* enemy3 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(2546, 160), 2446, 2626);
		m_enemies.push_back(enemy3);
		Enemy* enemy4 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(3448, 192), 3423, 3648);
		m_enemies.push_back(enemy4);
		Enemy* enemy5 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(3583, 192), 3423, 3648);
		m_enemies.push_back(enemy5);
		Enemy* enemy6 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(4083, 256), 4033, 4128);
		m_enemies.push_back(enemy6);
		Enemy* enemy7 = new Enemy("./Resources/Sprites/OverworldGoomba.png", sf::Vector2f(4418, 384), 4288, 4544);
		m_enemies.push_back(enemy7);

		MovingPlatform* movingPlatform1 = new MovingPlatform(sf::Vector2f(1802, 105), 100, 400);
		m_movingPlatforms.push_back(movingPlatform1);
		MovingPlatform* movingPlatform2 = new MovingPlatform(sf::Vector2f(2826, 200), 100, 400);
		m_movingPlatforms.push_back(movingPlatform2);
		MovingPlatform* movingPlatform3 = new MovingPlatform(sf::Vector2f(3026, 300), 100, 400);
		m_movingPlatforms.push_back(movingPlatform3);
		MovingPlatform* movingPlatform4 = new MovingPlatform(sf::Vector2f(4278, 300), 100, 350);
		m_movingPlatforms.push_back(movingPlatform4);
	}
}