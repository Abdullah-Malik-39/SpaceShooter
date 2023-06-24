#include "InstructionsScreen.h"

InstructionsScreen::InstructionsScreen(sf::RenderWindow* window) : window_(window)
{
    this->initGUI();
}

void InstructionsScreen::initGUI()
{
    //Load font
    if (!this->font_.loadFromFile("Resources/PixellettersFull.ttf"))
        std::cout << "ERROR::INSTRUCTIONS::Failed to load font" << "\n";

    title_.setFont(font_);
    title_.setString("Instructions");
    title_.setCharacterSize(100);
    title_.setFillColor(sf::Color::White);
    title_.setPosition(this->window_->getSize().x / 2 - title_.getLocalBounds().width / 2, 30);

    this->buttonTex.loadFromFile("Resources/Buttons/buttonRed.png");
    this->buttonSprite.setTexture(this->buttonTex);
    this->buttonSprite.setPosition((this->window_->getSize().x / 2) - this->buttonSprite.getGlobalBounds().width / 2, 700);
    backText_.setFont(font_);
    backText_.setString("Main Menu");
    backText_.setCharacterSize(24);
    backText_.setFillColor(sf::Color::Black);
    backText_.setPosition((this->window_->getSize().x / 2) - this->backText_.getGlobalBounds().width / 2, 700);
}

void InstructionsScreen::show()
{
    std::string instructions = "W A S D \t Move the ship \n\nSAPCE   \t Shoot \n\nP         \t Pause";

    sf::Text instructionsText;
    instructionsText.setFont(font_);
    instructionsText.setString(instructions);
    instructionsText.setCharacterSize(50);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setPosition(this->window_->getSize().x / 2 - instructionsText.getLocalBounds().width / 2, 200);

    bool running = true;

    while (running) {
        sf::Event event;
        while (this->window_->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->window_->close();
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = this->window_->mapPixelToCoords(sf::Mouse::getPosition(*this->window_));
                if (buttonSprite.getGlobalBounds().contains(mousePos)) {
                    running = false;
                }
            }
        }

        this->window_->clear(sf::Color::Black);
        this->window_->draw(title_);

        this->window_->draw(instructionsText);

        this->window_->draw(buttonSprite);
        this->window_->draw(backText_);

        this->window_->display();
    }
}
