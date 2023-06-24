#include "GameoverScreen.h"

GameOverScreen::GameOverScreen(sf::RenderWindow* window, std::int32_t s) : window_(window), Score(s)
{
    this->initGUI();
}

void GameOverScreen::initGUI()
{
    //Load font
    if (!this->font_.loadFromFile("Resources/PixellettersFull.ttf"))
        std::cout << "ERROR::GAME::Failed to load font" << "\n";

    this->buttonTex.loadFromFile("Resources/Buttons/buttonRed.png");
    this->buttonSprite.setTexture(this->buttonTex);
    this->buttonSprite.setPosition((this->window_->getSize().x / 2) - this->buttonSprite.getGlobalBounds().width / 2, 700);
    backText_.setFont(font_);
    backText_.setString("Main Menu");
    backText_.setCharacterSize(24);
    backText_.setFillColor(sf::Color::Black);
    backText_.setPosition((this->window_->getSize().x / 2) - this->backText_.getGlobalBounds().width / 2, 700);


    title_.setFont(font_);
    title_.setString("Game Over");
    title_.setCharacterSize(100);
    title_.setFillColor(sf::Color::White);
    title_.setPosition(this->window_->getSize().x / 2 - title_.getLocalBounds().width / 2, 30);

    Score_.setFont(font_);
    Score_.setString("Score : " + std::to_string(Score));
    Score_.setCharacterSize(60);
    Score_.setFillColor(sf::Color::White);
    Score_.setPosition(this->window_->getSize().x / 2 - Score_.getLocalBounds().width / 2, 300);
}

void GameOverScreen::show()
{
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

        this->window_->draw(Score_);

        this->window_->draw(buttonSprite);
        this->window_->draw(backText_);

        this->window_->display();
    }
}
