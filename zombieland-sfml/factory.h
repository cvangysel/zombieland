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

namespace sfml {

	class Factory : public zl::Factory {
	public:
		Factory(sf::RenderWindow& window) : window(window) { }
		virtual ~Factory() { }

		friend class Zombieland;
	protected:
		virtual zl::Zombie* createZombie(zl::Region*);
		virtual zl::Player* createPlayer(zl::Region*);

		virtual zl::Block* createBlock(const zl::Vector&, const zl::Vector&);

		sf::RenderWindow& window;
	};

}

#endif /* FACTORY_H_ */
