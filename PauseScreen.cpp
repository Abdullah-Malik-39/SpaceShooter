#include "PauseScreen.h"

PauseScreen::PauseScreen(sf::RenderWindow* window) : window_(window)
{
    this->initGUI();
}

void PauseScreen::initGUI()
{
    //Load font
    if (!this->font_.loadFromFile("Resources/PixellettersFull.ttf"))
        std::cout << "ERROR::GAME::Failed to load font" << "\n";

    this->buttonTex.loadFromFile("Resources/Buttons/buttonRed.png");
    this->buttonSprite.setTexture(this->buttonTex);
    this->buttonSprite.setPosition((this->window_->getSize().x / 2) - this->buttonSprite.getGlobalBounds().width / 2, 400);
    backText_.setFont(font_);
    backText_.setString("CONTINUE");
    backText_.setCharacterSize(24);
    backText_.setFillColor(sf::Color::Black);
    backText_.setPosition((this->window_->getSize().x / 2) - this->backText_.getGlobalBounds().width / 2, 400);

    this->buttonTex.loadFromFile("Resources/Buttons/buttonRed.png");
    this->ExitbuttonSprite.setTexture(this->buttonTex);
    this->ExitbuttonSprite.setPosition((this->window_->getSize().x / 2) - this->ExitbuttonSprite.getGlobalBounds().width / 2, 500);
    backText2_.setFont(font_);
    backText2_.setString("EXIT");
    backText2_.setCharacterSize(24);
    backText2_.setFillColor(sf::Color::Black);
    backText2_.setPosition((this->window_->getSize().x / 2) - this->backText2_.getGlobalBounds().width / 2, 500);


    title_.setFont(font_);
    title_.setString("Game Paused");
    title_.setCharacterSize(100);
    title_.setFillColor(sf::Color::White);
    title_.setPosition(this->window_->getSize().x / 2 - title_.getLocalBounds().width / 2, 30);
}

void PauseScreen::show()
{
    bool running = true;
    this->window_->setMouseCursorVisible(true);
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
                    this->window_->setMouseCursorVisible(false);
                    running = false;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = this->window_->mapPixelToCoords(sf::Mouse::getPosition(*this->window_));
                if (ExitbuttonSprite.getGlobalBounds().contains(mousePos)) {
                    this->window_->setMouseCursorVisible(true);
                    this->window_->close();
                    running = false;
                }
            }
        }

        this->window_->clear(sf::Color::Black);
        this->window_->draw(title_);

        this->window_->draw(Score_);

        this->window_->draw(buttonSprite);
        this->window_->draw(backText_);

        this->window_->draw(ExitbuttonSprite);
        this->window_->draw(backText2_);

        this->window_->display();
    }
}
