/*
 * object.h
 *
 *  Created on: Jan 30, 2013
 *      Author: cvangysel
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "vector.h"
#include "utils.h"

namespace zl {

	class Zombieland;
	class Object;

	class Handler {
	public:
		Handler() { }
		virtual ~Handler() { }

		virtual void handle(Zombieland&, const Object&) = 0;
	};

	class Object {
	public:
		Object(Handler* handler) : handler(handler) { }
		virtual ~Object() { }

		virtual void process(Zombieland&, unsigned int);

		virtual Vector getSize() const = 0;
		virtual Vector getPosition() const = 0;

		virtual Direction getDirection() const {
			return STATIONARY;
		};
	protected:
		Handler* handler;
	};

}

#endif /* OBJECT_H_ */
