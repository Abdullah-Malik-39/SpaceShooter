#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Monster
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

	sf::Sprite shipSprite;

	//Initializer functions
	void initVariables();

public:
	Monster();
	Monster(float pos_x, float pos_y, sf::Texture* ship);
	virtual ~Monster();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
	bool isDead();

	// Bullet shooting
	sf::Vector2f getPosition() const;
	float getHeight() const;
	bool canShoot();
	void resetShootTimer();
};
