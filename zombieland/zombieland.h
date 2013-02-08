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

		const Player& getPlayer() const;
		const list<Zombie*>& getZombies() const;
	private:
		void placeBlock(Vector, Vector);
		void spawnZombie();

		Factory& factory;

		Player* player;

		list<Object*> objects;
		list<Zombie*> zombies;
		list<const Obstacle*> obstacles;

		Terrain* terrain;
	};

}


#endif /* ZOMBIELAND_H_ */
