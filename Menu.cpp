#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : m_window(window), m_fileIO() {
    // Load font
    m_font.loadFromFile("Resources/PixellettersFull.ttf");

    //Load Textures
    this->textures["Blue"] = new sf::Texture();
    this->textures["Blue"]->loadFromFile("Resources/Buttons/buttonBlue.png");
    this->BlueButton.setTexture(*textures["Blue"]);
    this->textures["Green"] = new sf::Texture();
    this->textures["Green"]->loadFromFile("Resources/Buttons/buttonGreen.png");
    this->GreenButton.setTexture(*textures["Green"]);
    this->textures["Red"] = new sf::Texture();
    this->textures["Red"]->loadFromFile("Resources/Buttons/buttonRed.png");
    this->YellowButton.setTexture(*textures["Red"]);
    this->textures["Yellow"] = new sf::Texture();
    this->textures["Yellow"]->loadFromFile("Resources/Buttons/buttonYellow.png");
    this->RedButton.setTexture(*textures["Yellow"]);

    // Set up title
    m_title.setFont(m_font);
    m_title.setString("SPACE INVADERS");
    m_title.setCharacterSize(100);
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition((this->m_window.getSize().x / 2) - this->m_title.getGlobalBounds().width / 2, 50);
    
    //Start Button
    this->BlueButton.setPosition((this->m_window.getSize().x / 2) - this->BlueButton.getGlobalBounds().width / 2, 250);
    this->m_startButtonText.setFont(m_font);
    this->m_startButtonText.setString("START");
    this->m_startButtonText.setCharacterSize(24);
    this->m_startButtonText.setFillColor(sf::Color::Black);
    this->m_startButtonText.setPosition((this->m_window.getSize().x / 2) - this->m_startButtonText.getGlobalBounds().width / 2, 250);

    //Instructions button
    this->GreenButton.setPosition((this->m_window.getSize().x / 2) - this->GreenButton.getGlobalBounds().width / 2, 320);
    this->m_instructionsButtonText.setFont(m_font);
    this->m_instructionsButtonText.setString("INSTRUCTIONS");
    this->m_instructionsButtonText.setCharacterSize(24);
    this->m_instructionsButtonText.setFillColor(sf::Color::Black);
    this->m_instructionsButtonText.setPosition((this->m_window.getSize().x / 2) - this->m_instructionsButtonText.getGlobalBounds().width / 2, 320);

    //High Score Button
    this->YellowButton.setPosition((this->m_window.getSize().x / 2) - this->YellowButton.getGlobalBounds().width / 2, 390);
    this->m_highScoresButtonText.setFont(m_font);
    this->m_highScoresButtonText.setString("HIGH SCORES");
    this->m_highScoresButtonText.setCharacterSize(24);
    this->m_highScoresButtonText.setFillColor(sf::Color::Black);
    this->m_highScoresButtonText.setPosition((this->m_window.getSize().x / 2) - this->m_highScoresButtonText.getGlobalBounds().width / 2, 390);

    //Exit Button
    this->RedButton.setPosition((this->m_window.getSize().x / 2) - this->RedButton.getGlobalBounds().width / 2, 460);
    this->m_exitButtonText.setFont(m_font);
    this->m_exitButtonText.setString("EXIT");
    this->m_exitButtonText.setCharacterSize(24);
    this->m_exitButtonText.setFillColor(sf::Color::Black);
    this->m_exitButtonText.setPosition((this->m_window.getSize().x / 2) - this->m_exitButtonText.getGlobalBounds().width / 2, 460);

    // Set up player name prompt
    m_playerNamePrompt.setFont(m_font);
    m_playerNamePrompt.setString("Enter your name:");
    m_playerNamePrompt.setCharacterSize(40);
    m_playerNamePrompt.setFillColor(sf::Color::White);
    m_playerNamePrompt.setPosition((this->m_window.getSize().x / 2) - this->m_playerNamePrompt.getGlobalBounds().width / 2, 600);

    m_playerNameInput.setFont(m_font);
    m_playerNameInput.setCharacterSize(40);
    m_playerNameInput.setFillColor(sf::Color::White);
    m_playerNameInput.setPosition((this->m_window.getSize().x / 2) - this->m_playerNamePrompt.getGlobalBounds().width / 4, 640);
}

void Menu::draw() {
    m_window.draw(m_title);
    m_window.draw(this->BlueButton);
    m_window.draw(this->RedButton);
    m_window.draw(this->YellowButton);
    m_window.draw(this->GreenButton);
    m_window.draw(m_startButtonText);
    m_window.draw(m_instructionsButtonText);
    m_window.draw(m_highScoresButtonText);
    m_window.draw(m_exitButtonText);

    if (m_enteringPlayerName) {
        m_window.draw(m_playerNamePrompt);
        m_window.draw(m_playerNameInput);
    }
}

void Menu::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);

        if (BlueButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            // Start button pressed
            m_enteringPlayerName = true;
        }
        else if (GreenButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            // Instructions button pressed
            InstructionsScreen IS(&m_window);
            IS.show();
        }
        else if (YellowButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            // High scores button pressed
            HighScoreScreen HS(&m_window);
            HS.show();
        }
        else if (RedButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            // Exit button pressed
            m_window.close();
        }
    }
    else if (m_enteringPlayerName && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b' && m_playerNameInput.getString().getSize() > 0) {
            // Backspace pressed
            m_playerNameInput.setString(m_playerNameInput.getString().substring(0, m_playerNameInput.getString().getSize() - 1));
        }
        else if (event.text.unicode == '\r') {
            // Enter pressed
            std::string name = m_playerNameInput.getString();
            Game g(&m_window);
            bool result = g.run();
            if (result) {
                std::int32_t sc = g.getScore();
                m_fileIO.saveScore(name, sc);
                GameOverScreen GOS(&m_window, sc);
                m_window.setMouseCursorVisible(true);
                GOS.show();
            }
            m_enteringPlayerName = false;
            m_playerNameInput.setString("");
        }
        else if (event.text.unicode < 128) {
            // ASCII character entered
            m_playerNameInput.setString(m_playerNameInput.getString() + static_cast<char>(event.text.unicode));
        }
    }
}

Menu::~Menu() {
    // Nothing to clean up
}
