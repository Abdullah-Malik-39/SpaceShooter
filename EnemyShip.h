#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class EnemyShip
{
private:
	//Variables
	float speed;
	int hpMax;
	int hp;
	int damage;
	int points;
	float shootTimer;
	float shootTimerMax;
	std::string type;
	float hrSpeed;

	sf::Sprite shipSprite;

	//Initializer functions
	void initVariables();

public:
	EnemyShip(float pos_x, float pos_y, sf::Texture* ship, int lvl, std::string type);
	virtual ~EnemyShip();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
	void takeDamage();
	int getHP();

	// Bullet shooting
	sf::Vector2f getPosition() const;
	float getHeight() const;
	bool canShoot();
	void resetShootTimer();
};
