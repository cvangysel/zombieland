/*
 * zombieland.h
 *
 *  Created on: Jan 27, 2013
 *      Author: cvangysel
 */

#ifndef ZOMBIELAND_H_
#define ZOMBIELAND_H_

#include <list>

#include "event.h"
#include "factory.h"
#include "graph.h"

using std::list;

namespace zl {

	class Zombieland {
	public:
		Zombieland(Factory&, int, int);
		~Zombieland();

		void tick(unsigned int = 0);

		const Terrain& getTerrain() const;
		const Entity& getPlayer() const;
	private:
		Factory& factory;

		Entity* player;
		list<Object*> objects;
		Terrain* terrain;
	};

}


#endif /* ZOMBIELAND_H_ */
