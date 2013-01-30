/*
 * factory.h
 *
 *  Created on: Jan 27, 2013
 *      Author: cvangysel
 */

#ifndef FACTORY_H_
#define FACTORY_H_

#include "entity.h"
#include "obstacle.h"

namespace zl {

	class Factory {
	public:
		Factory() { };
		virtual ~Factory() { };

		friend class Zombieland;
	protected:
		virtual Zombie* createZombie(Region*) = 0;
		virtual Player* createPlayer(Region*) = 0;

		virtual Block* createBlock(const Vector&, const Vector&) = 0;
	};

}


#endif /* FACTORY_H_ */
