/*
 * entity.h
 *
 *  Created on: Jan 27, 2013
 *      Author: cvangysel
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <iostream>

#include "event.h"
#include "graph.h"
#include "object.h"

namespace zl {

	class Zombieland;
	class Entity;

	class Entity : public Object {
	public:
		Entity(Handler*, Region*);
		virtual ~Entity();

		virtual void process(Zombieland&, unsigned int);

		const Region& getRegion() const;

		Vector getSize() const;
		Vector getPosition() const;
	protected:
		Region* region;

		Vector size;
		Vector position;
		Vector direction;
	};

	class Zombie : public Entity {
	public:
		Zombie(Handler* handler, Region* location) : Entity(handler, location) { }

		virtual void process(Zombieland&, unsigned int);
	};

	class Player : public Entity {
	public:
		Player(Handler* handler, Region* location) : Entity(handler, location) { }

		virtual void process(Zombieland&, unsigned int);
	};

}

#endif /* ENTITY_H_ */
