#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "FileIO.h"

class HighScoreScreen {
public:
    HighScoreScreen(sf::RenderWindow* window);
    void show();

private:
    void initGUI();

    sf::Texture buttonTex;
    sf::Sprite buttonSprite;
    sf::RenderWindow* window_;
    sf::Font font_;
    sf::Text title_;
    sf::Text backText_;
    sf::RectangleShape backButton_;
    FileIO m_fileIO;
};
