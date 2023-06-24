#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class AddOns
{
private:
	//Variables
	float speed;

	sf::Sprite sprite;

	//Initializer functions
	void initVariables();

public:
	AddOns(float pos_x, float pos_y, sf::Texture* tex);

	virtual ~AddOns();

	//Accessors
	const sf::FloatRect getBounds() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};
