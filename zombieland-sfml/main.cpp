#include <SFML/Graphics.hpp>

#include <iostream>

#include "zombieland/zombieland.h"
#include "factory.h"

using std::cout;
using std::endl;

int main(int argc, char* arc[]) {
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Zombieland");
	window.setVerticalSyncEnabled(true);

	sfml::Factory factory(window);
	zl::Zombieland zombieland(factory, 10, 10);

	while (window.isOpen()) {
		unsigned int event = 0;

		sf::Event sfEvent;
		while (window.pollEvent(sfEvent)) {
			switch (sfEvent.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (sfEvent.key.code) {
				case sf::Keyboard::Up:
					event |= zl::Event::MOVE_UP;
					break;
				case sf::Keyboard::Right:
					event |= zl::Event::MOVE_RIGHT;
					break;
				case sf::Keyboard::Down:
					event |= zl::Event::MOVE_DOWN;
					break;
				case sf::Keyboard::Left:
					event |= zl::Event::MOVE_LEFT;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		// Clear screen
		window.clear();

		zombieland.tick(event);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}
