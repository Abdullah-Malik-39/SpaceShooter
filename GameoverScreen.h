#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "FileIO.h"

class GameOverScreen {
public:
    GameOverScreen(sf::RenderWindow* window, std::int32_t s);
    void show();

private:
    void initGUI();

    sf::Texture buttonTex;
    sf::Sprite buttonSprite;
    sf::RenderWindow* window_;
    sf::Font font_;
    sf::Text title_;
    sf::Text backText_;
    sf::Text Score_;
    std::int32_t Score;
};
