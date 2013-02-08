/*
 * exceptions.h
 *
 *  Created on: Feb 1, 2013
 *      Author: cvangysel
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>

using std::exception;

namespace zl {

	class Obstacle;

	class StuckException: public exception {
	public:

		StuckException(const Obstacle* obstacle, const Direction direction) : StuckException(obstacle, convert(direction)) { }
		StuckException(const Obstacle* obstacle, const Axis axis) : obstacle(obstacle), axis(axis) { }

		virtual const char* what() const throw() {
			return "Entity is stuck!";
		}

		const Obstacle* const obstacle;
		const Axis axis;
	};

}

#endif /* EXCEPTIONS_H_ */
