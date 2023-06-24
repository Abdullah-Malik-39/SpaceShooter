#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "FileIO.h"

class PauseScreen {
public:
    PauseScreen(sf::RenderWindow* window);
    void show();

private:
    void initGUI();

    sf::Texture buttonTex;
    sf::Sprite buttonSprite;
    sf::Sprite ExitbuttonSprite;
    sf::RenderWindow* window_;
    sf::Font font_;
    sf::Text title_;
    sf::Text backText_;
    sf::Text backText2_;
    sf::Text Score_;
    std::int32_t Score;
};
