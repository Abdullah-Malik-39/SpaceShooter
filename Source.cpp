#include <SFML/Graphics.hpp>
#include "Menu.h"

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Space Invaders", sf::Style::Close | sf::Style::Titlebar);
    
    // Load the custom cursor from an image file
    sf::Image cursorImage;
    if (!cursorImage.loadFromFile("Resources/cursor.png")) {
        // Handle error loading cursor image
    }

    // Create a cursor from the loaded image
    sf::Cursor cursor;
    if (!cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), { 0, 0 })) {
        // Handle error creating cursor
    }

    // Set the custom cursor as the mouse cursor for the window
    window.setMouseCursor(cursor);


    // Create the menu
    Menu menu(window);

    // Game loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                menu.handleInput(event);
            }
        }

        // Clear the window
        window.clear();

        // Draw the menu
        menu.draw();

        // Display the window
        window.display();
    }

    return 0;
}
