#include "EnemyShip.h"
#include <iostream>

void EnemyShip::initVariables()
{
	this->speed = static_cast<float>(0.5f);
	this->hpMax = static_cast<int>(1.f);
	this->hp = this->hpMax;
	this->damage = 1;
}

EnemyShip::EnemyShip(float pos_x, float pos_y, sf::Texture* ship, int lvl, std::string type)
{
	this->type = type;
	this->shipSprite.setTexture(*ship);
	this->shipSprite.setScale(0.6f, 0.6f);
	this->initVariables();
	this->shipSprite.setPosition(pos_x, pos_y);
	if(type == "ENEMYSHIP1")
	{
		this->shootTimerMax = 50.0f;
		this->points = (10 * lvl);
	}
	else if (type == "ENEMYSHIP2")
	{
		this->shootTimerMax = 30.0f;
		this->points = (20 * lvl);
	}
	else if (type == "ENEMYSHIP3")
	{
		this->shootTimerMax = 20.0f;
		this->points = (30 * lvl);
	}
	else if (type == "MONSTER")
	{
		this->hrSpeed = -0.7f;
		this->shipSprite.setScale(0.3f, 0.3f);
		this->hpMax = lvl * 10;
		this->hp = this->hpMax;
		this->shootTimerMax = 20.0f;
		this->points = 40;
	}
	this->shootTimer = this->shootTimerMax;
}

EnemyShip::~EnemyShip()
{

}

//Accessors
const sf::FloatRect EnemyShip::getBounds() const
{
	return this->shipSprite.getGlobalBounds();
}

const int& EnemyShip::getPoints() const
{
	return this->points;
}

const int& EnemyShip::getDamage() const
{
	return this->damage;
}

//Functions
void EnemyShip::update()
{
	this->shootTimer += 0.1f;
	this->shipSprite.move(0.f, this->speed);
	// Check if the enemy has reached the top of the screen
	if (this->shipSprite.getPosition().y > 40) {
		// Stop the enemy from moving
		this->speed = 0;
	}
	if(this->type == "MONSTER")
	{
		this->shipSprite.move(this->hrSpeed, 0.f);
		if (this->shipSprite.getPosition().x < 0 || this->shipSprite.getPosition().x > 800) {
			// Reverse the movement direction
			this->hrSpeed *= -1;
		}
	}
}

void EnemyShip::render(sf::RenderTarget* target)
{
	target->draw(this->shipSprite);
}

sf::Vector2f EnemyShip::getPosition() const
{
	return this->shipSprite.getPosition();
}

float EnemyShip::getHeight() const
{
	return this->shipSprite.getGlobalBounds().height;
}

bool EnemyShip::canShoot()
{
	if (this->shootTimer >= this->shootTimerMax) {
		return true;
	}
	return false;
}

void EnemyShip::resetShootTimer()
{
	this->shootTimer = 0.f;
}

void EnemyShip::takeDamage()
{
	this->hp -= 1;
}
int EnemyShip::getHP()
{
	return this->hp;
}
