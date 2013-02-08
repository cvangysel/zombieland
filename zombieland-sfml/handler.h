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

#include "resource.h"

namespace sfml {

	void updateSprite(const sf::Vector2u&, sf::Sprite&, const zl::Object&);

	class Handler : public zl::Handler {
	public:
		Handler(sf::RenderWindow& window, const sfml::Resources<ResourceIdentifier>& resources) : zl::Handler(), resources(resources), window(window), sprite(0) {
		}
		virtual ~Handler();
	protected:
		const sfml::Resources<ResourceIdentifier>& resources;

		sf::RenderWindow& window;
		sf::Sprite* sprite;
	};

	class EntityHandler : public sfml::Handler {
	public:
		EntityHandler(sf::RenderWindow&, const sfml::Resources<ResourceIdentifier>&);
		virtual ~EntityHandler() { }

		void handle(zl::Zombieland&, const zl::Object&);
	};

	class ObstacleHandler : public sfml::Handler {
	public:
		ObstacleHandler(sf::RenderWindow&, const sfml::Resources<ResourceIdentifier>&);
		virtual ~ObstacleHandler() { }

		void handle(zl::Zombieland&, const zl::Object&);
	};

}

#endif /* HANDLER_H_ */
