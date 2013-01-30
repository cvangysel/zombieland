/*
 * object.h
 *
 *  Created on: Jan 30, 2013
 *      Author: cvangysel
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <utility>
#include <iostream>

namespace zl {

	typedef std::pair<double, double> Vector;

	zl::Vector operator+(const zl::Vector&, const zl::Vector&);
	zl::Vector operator+=(zl::Vector&, const zl::Vector&);
	zl::Vector operator-(const zl::Vector&, const zl::Vector&);
	zl::Vector operator/(const zl::Vector&, double);
	zl::Vector operator*(const zl::Vector&, double);
	bool operator>=(const zl::Vector&, const zl::Vector&);
	bool operator<=(const zl::Vector&, const zl::Vector&);

	std::ostream& operator<<(std::ostream& cout, const Vector& vector);

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
	protected:
		Handler* handler;
	};

}

#endif /* OBJECT_H_ */
