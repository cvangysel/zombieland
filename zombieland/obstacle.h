/*
 * obstacle.h
 *
 *  Created on: Jan 30, 2013
 *      Author: cvangysel
 */

#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "object.h"

namespace zl {

	class Obstacle : public Object {
	public:
		Obstacle(Handler*, const Vector&);
		virtual ~Obstacle() { }

		bool intersects(const Vector&) const;
		bool intersects(const Vector&, const Vector&) const;

		virtual Vector getPosition() const { return this->position; }
	protected:
		Vector position;

		Vector minBound;
		Vector maxBound;
	};

	class Block : public Obstacle {
	public:
		Block(Handler*, const Vector&, const Vector&);

		virtual Vector getSize() const { return this->size; };
	protected:
		Vector size;
	};

}


#endif /* OBSTACLE_H_ */
