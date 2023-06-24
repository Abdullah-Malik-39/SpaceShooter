#include "HighScoreScreen.h"

HighScoreScreen::HighScoreScreen(sf::RenderWindow* window) : window_(window), m_fileIO()
{
	this->initGUI();
}

void HighScoreScreen::initGUI()
{
	//Load font
	if (!this->font_.loadFromFile("Resources/PixellettersFull.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	title_.setFont(font_);
	title_.setString("High Scores");
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

	float backTextWidth = backText_.getLocalBounds().width;
	float backTextHeight = backText_.getLocalBounds().height;

	backButton_.setSize(sf::Vector2f(backTextWidth + 20, backTextHeight + 20));
	backButton_.setFillColor(sf::Color::Blue);
	backButton_.setPosition(50, this->window_->getSize().y - backButton_.getSize().y - 50);

}

void HighScoreScreen::show()
{
	std::vector<sf::Text> scoreTexts;
	std::vector<Score> scores = m_fileIO.loadScores();
	int i = 0;
	for (const Score& score : scores)
	{
		if (i > 4)
		{
			break;
		}
		std::string scoreStr = score.name;
		scoreStr.append(30 - score.name.length(), ' '); // Add padding to the name
		scoreStr += ":  ";
		scoreStr += std::to_string(score.score);
		scoreStr.append(5 - std::to_string(score.score).length(), ' '); // Add padding to the score

		sf::Text text;
		text.setFont(font_);
		text.setString(scoreStr);
		text.setCharacterSize(40);
		text.setFillColor(sf::Color::White);
		text.setPosition(this->window_->getSize().x / 2 - text.getLocalBounds().width / 2, 150 + i * (text.getLocalBounds().height + 20));
		i += 1;
		scoreTexts.push_back(text);
	}

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

		for (const auto& text : scoreTexts) {
			this->window_->draw(text);
		}

		this->window_->draw(buttonSprite);
		this->window_->draw(backText_);

		this->window_->display();
	}
}
