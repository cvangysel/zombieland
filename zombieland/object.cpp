/*
 * object.cpp
 *
 *  Created on: Jan 30, 2013
 *      Author: cvangysel
 */

#include "object.h"

void zl::Object::process(Zombieland& game, unsigned int event) {
	this->handler->handle(game, *this);
}
