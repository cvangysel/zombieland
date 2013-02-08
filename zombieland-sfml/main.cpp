#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "zombieland/zombieland.h"
#include "factory.h"

using std::cout;
using std::endl;

int main(int argc, char* arc[]) {
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 800), "Pacman Revenge");
	window.setVerticalSyncEnabled(true);

	sfml::Factory factory(window);
	zl::Zombieland zombieland(factory, 10, 10);

	sf::Clock clock;

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

		// Time in seconds to render one frame
		float t_frame = clock.restart().asSeconds();

		// Display frames per second
		std::stringstream fps_stream;
		fps_stream << "FPS: " << floor(1.0f / t_frame);
		std::string fps_str(fps_stream.str());
		sf::Text fps_text(fps_str);

		// Clear screen
		window.clear();

		zombieland.tick(event);

		window.draw(fps_text);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}
