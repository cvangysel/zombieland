/*
 * vector.h
 *
 *  Created on: Feb 1, 2013
 *      Author: cvangysel
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <utility>
#include <iostream>

#include "utils.h"

namespace zl {

	class Vector {
	public:
		Vector();
		Vector(double);
		Vector(double, double);
		Vector(const Direction&);
		Vector(const Direction&, const Direction&);

		Vector& operator=(double);
		Vector& operator-();

		void set(const Axis, double);
		double get(const Axis);

		std::pair<Direction, Direction> getDirections() const;

		double first;
		double second;
	};

	zl::Vector operator+(const zl::Vector&, const zl::Vector&);
	zl::Vector operator+=(zl::Vector&, const zl::Vector&);
	zl::Vector operator-(const zl::Vector&, const zl::Vector&);
	zl::Vector operator/(const zl::Vector&, double);
	zl::Vector operator/=(zl::Vector&, double);
	zl::Vector operator*(const zl::Vector&, double);
	zl::Vector operator*=(zl::Vector&, double);
	bool operator>=(const zl::Vector&, const zl::Vector&);
	bool operator<=(const zl::Vector&, const zl::Vector&);

	double euclidianNorm(const zl::Vector&);
	zl::Vector normalize(const zl::Vector&);

	std::ostream& operator<<(std::ostream& cout, const Vector& vector);

}


#endif /* VECTOR_H_ */
