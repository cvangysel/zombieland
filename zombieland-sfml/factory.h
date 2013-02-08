/*
 * factory.h
 *
 *  Created on: Jan 27, 2013
 *      Author: cvangysel
 */

#ifndef FACTORY_SFML_H_
#define FACTORY_SFML_H_

#include <SFML/Graphics.hpp>

#include "zombieland/factory.h"

#include "resource.h"

namespace sfml {

	class Factory : public zl::Factory {
	public:
		Factory(sf::RenderWindow&);
		virtual ~Factory();

		friend class Zombieland;
	protected:
		virtual zl::Zombie* createZombie(const zl::Zombieland*);
		virtual zl::Player* createPlayer(const zl::Zombieland*);

		virtual zl::Block* createBlock(const zl::Vector&, const zl::Vector&);

		sf::RenderWindow& window;

		PlayerResources playerResources;
		Resources<ResourceIdentifier>* zombieResources[4];
		Resources<ResourceIdentifier> obstacleResources;
	};

}

#endif /* FACTORY_H_ */
