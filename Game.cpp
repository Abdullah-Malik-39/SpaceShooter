#include "Game.h"

//Private functions
void Game::initWindow()
{
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
	this->window->setMouseCursorVisible(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Resources/laserBlue01.png");

	this->textures["ENEMYSHIP1"] = new sf::Texture();
	this->textures["ENEMYSHIP1"]->loadFromFile("Resources/enemy_1.png");
	this->textures["ENEMYSHIP2"] = new sf::Texture();
	this->textures["ENEMYSHIP2"]->loadFromFile("Resources/enemy_2.png");
	this->textures["ENEMYSHIP3"] = new sf::Texture();
	this->textures["ENEMYSHIP3"]->loadFromFile("Resources/enemy_3.png");

	this->textures["ENEMYSHIPBULLET"] = new sf::Texture();
	this->textures["ENEMYSHIPBULLET"]->loadFromFile("Resources/enemy_laser.png");

	this->textures["MONSTER"] = new sf::Texture();
	this->textures["MONSTER"]->loadFromFile("Resources/monster1.png");
}

void Game::initAudio() {
	if (!this->laserSoundBuffer.loadFromFile("Resources/Laser-shot.wav"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD LASER SOUND" << "\n";
	}
	this->laserSound.setBuffer(laserSoundBuffer);
}

void Game::initGUI()
{
	if (!this->playerHpTex.loadFromFile("Resources/heart.png"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD PLAYER HEARTS TEXTURE" << "\n";
	}
	this->playerHpSp = std::vector<sf::Sprite>(3, sf::Sprite(playerHpTex));
	for (int i = 0;i < playerHpSp.size();i++) {
		this->playerHpSp[i].setScale(0.03f, 0.03f);
		this->playerHpSp[i].setPosition(20.f + (i * 25), 15.f);
	}

	//Load font
	if (!this->font.loadFromFile("Resources/PixellettersFull.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	//Init point text
	this->pointText.setPosition(850.f, 0.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(35);
	this->pointText.setFillColor(sf::Color::Yellow);
	this->pointText.setString("test");
	
	this->level = 1;
	this->LevelText.setFont(this->font);
	this->LevelText.setCharacterSize(80);
	this->LevelText.setFillColor(sf::Color::Yellow);
	this->LevelText.setString("Level : "+ std::to_string(this->level));
	this->LevelText.setPosition(
		this->window->getSize().x / 2.f - this->LevelText.getGlobalBounds().width / 2.f,
		(this->window->getSize().y / 2.f - this->LevelText.getGlobalBounds().height / 2.f) - 20.f);
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Resources/background.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	sf::Vector2f targetSize(1000.0f, 800.0f);
	this->worldBackground.setTexture(this->worldBackgroundTex);
	this->worldBackground.setScale(
		targetSize.x / worldBackground.getLocalBounds().width,
		targetSize.y / worldBackground.getLocalBounds().height);
}

void Game::initSystems()
{
	this->points = 0;
	this->enemiesSpawned = 0;
	this->enemiesKilled = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
	sf::Vector2f PlayerSpawn(475.f, 800.f);
	this->player->setPosition(PlayerSpawn);
}

void Game::initEnemies()
{
	//2000 best for AddOns
	this->spawnTimerMax = 150.f;
	this->spawnTimerMaxAestroids = 50.f;
	this->spawnTimer = this->spawnTimerMax;
	
}


Game::Game(sf::RenderWindow* window) : window(window) {
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSystems();
	this->initAudio();

	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->player;

	//Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//Delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}
}

//Functions
bool Game::run()
{
	// Show LevelText for 1 second before the game actually starts
	sf::Clock clock;
	while (clock.getElapsedTime().asSeconds() < 1.f)
	{
		this->window->clear();
		this->window->draw(this->LevelText);
		this->window->display();
	}
	while (this->window->isOpen())
	{
		if (isGameOver() || this->level>3) {
			return true; // Return false to indicate that the game is over
		}
		else if (this->enemiesKilled == 10*this->level) {
			this->level += 1;
			this->reset();
			if (this->level > 3)
				return true;
			this->LevelText.setString("Level : " + std::to_string(this->level));
			this->run();
		}
		this->updatePollEvents();

		if (this->player->getHp() > 0)
			this->update();

		this->render();
	}
}

void Game::reset()
{
	this->enemyships.clear();
	this->bullets.clear();
}
void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		PauseScreen PS(this->window);
		PS.show();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack())
	{
		laserSound.play();
		this->bullets.push_back(
			new Bullet(
				this->textures["BULLET"],
				this->player->getPos().x + this->player->getBounds().width / 2.f - this->textures["BULLET"]->getSize().x / 2,
				this->player->getPos().y-50,
				0.f,
				-1.f,
				5.f,
				"player"
			)
		);
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Points: " << this->points;

	this->pointText.setString(ss.str());
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//Left world collision
	if (this->player->getBounds().left < 0.f - this->player->width() / 2)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	//Right world collison
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x + this->player->width() / 2)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}

	//Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}
		else if (bullet->getBounds().height + bullet->getBounds().height > this->window->getSize().y)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}
		++counter;
	}
}
  
void Game::updateEnemies()
{
	//Spawning
	if (level == 1 && this->enemiesSpawned <9) {
		this->spawnTimer += 0.5f;
		std::string type = this->getRandEnemyTex();
		if (this->spawnTimer >= this->spawnTimerMax)
		{
			this->enemyships.push_back(new EnemyShip((rand() % (this->window->getSize().x - this->textures[type]->getSize().x)), -100.f, this->textures[type], this->level, type));
			this->spawnTimer = 0.f;
			this->enemiesSpawned += 1;
		}
	}
	else if (level == 2 && this->enemiesSpawned < 19) {
		this->spawnTimer += 0.8f;
		std::string type = this->getRandEnemyTex();
		if (this->spawnTimer >= this->spawnTimerMax)
		{
			this->enemyships.push_back(new EnemyShip((rand() % (this->window->getSize().x - this->textures[type]->getSize().x)), -100.f, this->textures[type], this->level, type));
			this->spawnTimer = 0.f;
			this->enemiesSpawned += 1;
		}
	}
	else if (level == 3 && this->enemiesSpawned < 29) {
		this->spawnTimer += 1.2f;
		std::string type = this->getRandEnemyTex();
		if (this->spawnTimer >= this->spawnTimerMax)
		{
			this->enemyships.push_back(new EnemyShip((rand() % (this->window->getSize().x - this->textures[type]->getSize().x)), -100.f, this->textures[type], this->level, type));
			this->spawnTimer = 0.f;
			this->enemiesSpawned += 1;
		}
	}
	else if(this->enemiesKilled == this->enemiesSpawned) {
		this->spawnTimer += 1.2f;
		this->addon.push_back(new AddOns(100.f,-100.f,&this->playerHpTex));
		this->enemyships.push_back(new EnemyShip((rand() % (this->window->getSize().x - this->textures["MONSTER"]->getSize().x)), -100.f, this->textures["MONSTER"], this->level, "MONSTER"));
		this->spawnTimer = 0.f;
		this->enemiesSpawned += 1;
	}
	
	//Update
	this->updateEnemyShips();
	this->updateEnemyBullets();
	this->updateAddons();
}

std::string Game::getRandEnemyTex() {
	srand(time(0));
	std::string str = "ENEMYSHIP";
	int randomNumber = rand() % 3 + 1;
	str += std::to_string(randomNumber);
	return str;
}

void::Game::updateEnemyBullets() {
	int counter = 0;
	for (auto* bullet : this->bullets)
	{
		//Enemy player collision
		if (bullet->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(1);
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			this->playerHpSp.pop_back();
		}

		++counter;
	}
}

void::Game::updateEnemyShips() {
	unsigned counter = 0;
	for (auto* enemy : this->enemyships)
	{
		bool enemy_deleted = false;
		enemy->update();

		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemyships.at(counter);
			this->enemyships.erase(this->enemyships.begin() + counter);
			enemy_deleted = true;
		}
		//Enemy player collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemyships.at(counter)->getDamage());
			delete this->enemyships.at(counter);
			this->enemyships.erase(this->enemyships.begin() + counter);
			this->playerHpSp.pop_back();
			enemy_deleted = true;
			this->enemiesKilled+=1;
		}
		// Enemy firing
		if (!enemy_deleted && enemy->canShoot())
		{
			this->bullets.push_back(new Bullet(this->textures["ENEMYSHIPBULLET"], enemy->getPosition().x + enemy->getBounds().width / 2.f - (this->textures["ENEMYSHIPBULLET"]->getSize().x /2),
				enemy->getPosition().y + enemy->getBounds().height, 0.f, 1.f, 5.f,"enemy"));
			enemy->resetShootTimer();
		}
		++counter;
	}
}
void::Game::updateAddons() {
	unsigned counter = 0;
	for (auto* add : this->addon)
	{
		bool add_deleted = false;
		add->update();

		//Addon culling (bottom of screen)
		if (add->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->addon.at(counter);
			this->addon.erase(this->addon.begin() + counter);
			add_deleted = true;
		}
		//Enemy player collision
		else if (add->getBounds().intersects(this->player->getBounds()))
		{
			this->player->AddHp();
			delete this->addon.at(counter);
			this->addon.erase(this->addon.begin() + counter);
			sf::Sprite sp;
			sp.setTexture(playerHpTex);
			sp.setScale(0.03f, 0.03f);
			if (this->playerHpSp.size() < 3) {
				sp.setPosition(20.f + (this->playerHpSp.size() * 25), 15.f);
				this->playerHpSp.push_back(sp);
			}
			add_deleted = true;
		}
		++counter;
	}
}


void Game::updateCombat()
{
	for (int i = 0; i < this->enemyships.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemyships[i]->getBounds().intersects(this->bullets[k]->getBounds()) && this->bullets[k]->getType() == "player")
			{
				this->enemyships[i]->takeDamage();
				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);
				if(this->enemyships[i]->getHP() <= 0)
				{
					this->points += this->enemyships[i]->getPoints();

					delete this->enemyships[i];
					this->enemyships.erase(this->enemyships.begin() + i);

					this->enemiesKilled += 1;
					enemy_deleted = true;
				}
			}
		}
	}
}

void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();  

	this->updateGUI();

	this->updateWorld();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	for (int i = 0;i < playerHpSp.size();i++)
		this->window->draw(this->playerHpSp[i]);
}

int Game::getScore()
{
	return this->points;
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();

	//Draw world
	this->renderWorld();

	//Draw all the stuffs
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemyships)
	{
		enemy->render(this->window);
	}

	for (auto* add : this->addon)
	{
		add->render(this->window);
	}

	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0)
	{
		this->gameOver = true; // Set the game over flag
	}

	this->window->display();
}

bool Game::isGameOver() const {
	return this->gameOver;
}