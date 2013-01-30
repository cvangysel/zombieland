/*
 * obstacle.cpp
 *
 *  Created on: Jan 30, 2013
 *      Author: cvangysel
 */

#include <iostream>

#include "obstacle.h"

using std::cout;
using std::endl;

zl::Obstacle::Obstacle(Handler* handler, const Vector& position) : Object(handler), position(position) { }

bool zl::Obstacle::intersects(const Vector& position) const {
	return (position.first >= this->minBound.first && position.first <= this->maxBound.first)
			&& (position.second >= this->minBound.second && position.second <= this->maxBound.second);
}

bool zl::Obstacle::intersects(const Vector& minBound, const Vector& maxBound) const {
	return !((maxBound.first <= this->minBound.first) || (minBound.first >= this->maxBound.first) ||
			(maxBound.second <= this->minBound.second) || (minBound.second >= this->maxBound.second));
}

zl::Block::Block(Handler* handler, const Vector& position, const Vector& size) : Obstacle(handler, position), size(size) {
	this->minBound = position - (this->getSize() / 2);
	this->maxBound = position + (this->getSize() / 2);
}
