/*
 * utils.h
 *
 *  Created on: Jan 28, 2013
 *      Author: cvangysel
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <unordered_map>
#include <iterator>
#include <utility>

namespace zl {

	enum Direction {
		STATIONARY = -1,
		UP = 0,
		RIGHT = 1,
		DOWN = 2,
		LEFT = 3
	};

	Direction invert(Direction);
	std::ostream& operator<<(std::ostream&, const Direction&);

	enum Axis {
		BOTH,
		HORIZONTAL,
		VERTICAL
	};

	Axis invert(Axis);
	Axis convert(Direction);
	std::ostream& operator<<(std::ostream&, const Axis&);
	std::pair<Direction, Direction> convert(Axis);

}

#endif /* UTILS_H_ */
