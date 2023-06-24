#include "AddOns.h"

void AddOns::initVariables()
{
	this->speed = 0.5f;
}

AddOns::AddOns(float pos_x, float pos_y, sf::Texture* tex)
{
	this->sprite.setTexture(*tex);
	this->sprite.setScale(0.03f, 0.03f);
	this->initVariables();
	this->sprite.setPosition(pos_x, pos_y);
}


AddOns::~AddOns()
{
}

const sf::FloatRect AddOns::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void AddOns::update()
{
	this->sprite.move(0.f, this->speed);
}

void AddOns::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
