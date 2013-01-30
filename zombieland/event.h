/*
 * event.h
 *
 *  Created on: Jan 28, 2013
 *      Author: cvangysel
 */

#ifndef EVENT_H_
#define EVENT_H_

namespace zl {

	enum Event {
		NONE 		= 0,
		MOVE_UP 	= 1u << 0,
		MOVE_LEFT 	= 1u << 1,
		MOVE_DOWN	= 1u << 2,
		MOVE_RIGHT	= 1u << 3
	};

}

#endif /* EVENT_H_ */
