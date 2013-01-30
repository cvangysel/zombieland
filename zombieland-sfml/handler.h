/*
 * handler.h
 *
 *  Created on: Jan 27, 2013
 *      Author: cvangysel
 */

#ifndef HANDLER_H_
#define HANDLER_H_

#include <SFML/Graphics.hpp>

#include "zombieland/zombieland.h"

namespace sfml {

	void updateSprite(const sf::Vector2u&, sf::Sprite&, const zl::Object&);

	class Handler : public zl::Handler {
	public:
		Handler(sf::RenderWindow& window) : zl::Handler(), window(window), sprite(0) { }
		virtual ~Handler();
	protected:
		sf::RenderWindow& window;
		sf::Sprite* sprite;
	};

	class EntityHandler : public sfml::Handler {
	public:
		EntityHandler(sf::RenderWindow&);
		virtual ~EntityHandler() { }

		void handle(zl::Zombieland&, const zl::Object&);
	};

	class ObstacleHandler : public sfml::Handler {
	public:
		ObstacleHandler(sf::RenderWindow&);
		virtual ~ObstacleHandler() { }

		void handle(zl::Zombieland&, const zl::Object&);
	};

}

#endif /* HANDLER_H_ */
