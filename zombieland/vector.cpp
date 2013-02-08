/*
 * vector.cpp
 *
 *  Created on: Feb 1, 2013
 *      Author: cvangysel
 */

#include <iostream>
#include <cmath>
#include <math.h>

#include "vector.h"

using std::cout;
using std::endl;

zl::Vector::Vector() : first(0), second(0) { }

zl::Vector::Vector(double x) : first(x), second(x) { }

zl::Vector::Vector(double x, double y) : first(x), second(y) { }

zl::Vector::Vector(const zl::Direction& direction) : Vector(direction, direction) { }

zl::Vector::Vector(const zl::Direction& x, const zl::Direction& y) : first(0), second(0) {
	if (x == LEFT) {
		this->first = -1.;
	} else if (x == RIGHT) {
		this->first = 1.;
	}

	if (y == UP) {
		this->second = -1.;
	} else if (x == DOWN) {
		this->second = 1.;
	}
}

zl::Vector& zl::Vector::operator=(double x) {
	this->first = x;
	this->second = x;

	return *this;
}

zl::Vector& zl::Vector::operator-() {
	this->first = - this->first;
	this->second = - this->second;

	return *this;
}

void zl::Vector::set(const Axis axis, double x) {
	switch (axis) {
	case HORIZONTAL:
		this->first = x;
		break;
	case VERTICAL:
		this->second = x;
		break;
	default:
		break;
	}
}

double zl::Vector::get(const Axis axis) {
	switch (axis) {
		case HORIZONTAL:
			return this->first;
		case VERTICAL:
			return this->second;
		default:
			return 0. / 0.;
		}
}

std::pair<zl::Direction, zl::Direction> zl::Vector::getDirections() const {
	std::pair<zl::Direction, zl::Direction> directions(STATIONARY, STATIONARY);

	if (this->first > 0) {
		directions.first = RIGHT;
	} else if (this->first < 0) {
		directions.first = LEFT;
	}

	if (this->second > 0) {
		directions.second = DOWN;
	} else if (this->second < 0) {
		directions.second = UP;
	}

	return directions;
}

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

zl::Vector zl::operator/=(zl::Vector& a, double scalar) {
	a.first /= scalar;
	a.second /= scalar;

	return a;
}

zl::Vector zl::operator*(const zl::Vector& a, double scalar) {
	return zl::Vector(a.first * scalar, a.second * scalar);
}

zl::Vector zl::operator*=(zl::Vector& a, double scalar) {
	a.first *= scalar;
	a.second *= scalar;

	return a;
}

bool zl::operator>=(const zl::Vector& a, const zl::Vector& b) {
	return a.first >= b.first && a.second >= b.second;
}

bool zl::operator<=(const zl::Vector& a, const zl::Vector& b) {
	return a.first <= b.first && a.second <= b.second;
}

double zl::euclidianNorm(const zl::Vector& a) {
	double x = std::isnan(a.first) ? 0 : a.first;
	double y = std::isnan(a.second) ? 0 : a.second;

	return sqrt(x * x + y * y);
}

zl::Vector zl::normalize(const zl::Vector& a) {
	double norm = euclidianNorm(a);

	if (norm) {
		return a / norm;
	} else {
		return 0;
	}
}

std::ostream& zl::operator<<(std::ostream& cout, const Vector& vector) {
	cout << "(" << vector.first << ", " << vector.second << ")";
	return cout;
}
