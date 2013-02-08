/*
 * utils.cpp
 *
 *  Created on: Jan 28, 2013
 *      Author: cvangysel
 */

#include "utils.h"

zl::Direction zl::invert(Direction direction) {
	switch (direction) {
	case UP:
		return DOWN;
	case DOWN:
		return UP;
	case LEFT:
		return RIGHT;
	case RIGHT:
		return LEFT;
	default:
		return STATIONARY;
	}
}

std::ostream& zl::operator<<(std::ostream& cout, const Direction& direction) {
	switch (direction) {
	case UP:
		cout << "UP";
		break;
	case DOWN:
		cout << "DOWN";
		break;
	case LEFT:
		cout << "LEFT";
		break;
	case RIGHT:
		cout << "RIGHT";
		break;
	default:
		cout << "STATIONARY";
		break;
	}

	return cout;
}

zl::Axis zl::invert(zl::Axis axis) {
	switch (axis) {
	case HORIZONTAL:
		return VERTICAL;
	case VERTICAL:
		return HORIZONTAL;
	case BOTH:
		return BOTH;
	}
}

zl::Axis zl::convert(Direction direction) {
	switch (direction) {
	case LEFT:
	case RIGHT:
		return HORIZONTAL;
	case UP:
	case DOWN:
		return VERTICAL;
	default:
		return BOTH;
	}
}

std::ostream& zl::operator<<(std::ostream& cout, const Axis& axis) {
	switch (axis) {
	case HORIZONTAL:
		cout << "HORIZONTAL";
		break;
	case VERTICAL:
		cout << "VERTICAL";
		break;
	default:
		cout << "BOTH";
		break;
	}

	return cout;
}

std::pair<zl::Direction, zl::Direction> zl::convert(zl::Axis axis) {
	switch (axis) {
	case HORIZONTAL:
		return {LEFT, RIGHT};
	case VERTICAL:
		return {UP, DOWN};
	case BOTH:
		return {STATIONARY, STATIONARY};
	}
}
