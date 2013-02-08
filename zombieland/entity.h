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

	typedef std::pair<const Obstacle*, const Obstacle*> Obstacles;

	class Zombieland;
	class Entity;

	class Entity : public Object {
	public:
		Entity(const Zombieland*, Handler*, double);
		virtual ~Entity();

		virtual void process(Zombieland&, unsigned int);

		const Region& getRegion() const;

		virtual Vector getSize() const;
		virtual Vector getPosition() const;

		virtual Direction getDirection() const;
	protected:
		Region* region;

		Vector size;
		Vector position;

		double velocity;
		Vector direction;
		Obstacles blocked;
	};

	class Zombie : public Entity {
	public:
		Zombie(const Zombieland*, Handler* handler);

		virtual void process(Zombieland&, unsigned int);
	};

	class Player : public Entity {
	public:
		Player(const Zombieland*, Handler* handler);

		virtual void process(Zombieland&, unsigned int);

		Direction getDirection(const Region*) const;
	protected:
		PathInformation pathInformation;
	};

}

#endif /* ENTITY_H_ */
