#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "FileIO.h"
#include "Game.h"
#include "FileIO.h"
#include "HighScoreScreen.h"
#include "InstructionsScreen.h"
#include "GameoverScreen.h"

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void draw();
    void handleInput(sf::Event& event);
    ~Menu();

private:
    sf::RenderWindow& m_window;
    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_startButtonText;
    sf::Text m_instructionsButtonText;
    sf::Text m_highScoresButtonText;
    sf::Text m_exitButtonText;
    FileIO m_fileIO;

    bool m_enteringPlayerName = false;
    sf::Text m_playerNamePrompt;
    sf::Text m_playerNameInput;

    std::map<std::string, sf::Texture*> textures;
    sf::Sprite BlueButton;
    sf::Sprite GreenButton;
    sf::Sprite RedButton;
    sf::Sprite YellowButton;
};

#endif // MENU_H
