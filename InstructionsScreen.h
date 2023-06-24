#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class InstructionsScreen
{
public:
    InstructionsScreen(sf::RenderWindow* window);

    void show();

private:
    void initGUI();

private:
    sf::Texture buttonTex;
    sf::Sprite buttonSprite;
    sf::RenderWindow* window_;
    sf::Font font_;
    sf::Text title_;
    sf::RectangleShape backButton_;
    sf::Text backText_;
};
