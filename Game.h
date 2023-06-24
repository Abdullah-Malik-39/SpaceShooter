#pragma once

#include<map>
#include<string>
#include<iostream>
#include<sstream>
#include"Player.h"
#include"Bullet.h"
#include"EnemyShip.h"
#include"SFML/Audio.hpp"
#include"PauseScreen.h"
#include"AddOns.h"

class Game
{
private:
	//Addons
	std::vector<AddOns*> addon;

	int enemiesSpawned;
	int enemiesKilled;

	//Sounds
	sf::SoundBuffer laserSoundBuffer;
	sf::Sound laserSound;

	//Window
	sf::RenderWindow* window;
	bool gameOver;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;
	sf::Text LevelText;

	//Game Level
	int level;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Systems
	unsigned points;

	//Player
	Player* player;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;
	sf::Texture playerHpTex;
	std::vector<sf::Sprite> playerHpSp;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	float spawnTimerMaxAestroids;
	std::vector<EnemyShip*> enemyships;

	//Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();
	void initAudio();
	void reset();
	std::string getRandEnemyTex();

	void initPlayer();
	void initEnemies();
    bool isGameOver() const;
	void updateEnemyBullets();
	void updateEnemyShips();
	void updateAddons();

public:
	//Game();
	Game(sf::RenderWindow* window);
	virtual ~Game();

	//Functions
	bool run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();
	int getScore();

	void renderGUI();
	void renderWorld();
	void render();
};
