/*
 * object.cpp
 *
 *  Created on: Jan 30, 2013
 *      Author: cvangysel
 */

#include <iostream>

#include "object.h"

using std::cout;
using std::endl;

zl::Vector zl::operator+(const zl::Vector& a, const zl::Vector& b) {
	return zl::Vector(a.first + b.first, a.second + b.second);
}

zl::Vector zl::operator+=(zl::Vector& a, const zl::Vector& b) {
	a.first += b.first;
	a.second += b.second;

	return a;
}

zl::Vector zl::operator-(const zl::Vector& a, const zl::Vector& b) {
	return zl::Vector(a.first - b.first, a.second - b.second);
}

zl::Vector zl::operator/(const zl::Vector& a, double scalar) {
	return zl::Vector(a.first / scalar, a.second / scalar);
}

zl::Vector zl::operator*(const zl::Vector& a, double scalar) {
	return zl::Vector(a.first * scalar, a.second * scalar);
}

bool zl::operator>=(const zl::Vector& a, const zl::Vector& b) {
	return a.first >= b.first && a.second >= b.second;
}

bool zl::operator<=(const zl::Vector& a, const zl::Vector& b) {
	return a.first <= b.first && a.second <= b.second;
}

std::ostream& zl::operator<<(std::ostream& cout, const Vector& vector) {
	cout << "(" << vector.first << ", " << vector.second << ")";
	return cout;
}

void zl::Object::process(Zombieland& game, unsigned int event) {
	this->handler->handle(game, *this);
}
