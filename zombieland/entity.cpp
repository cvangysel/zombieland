/*
 * entity.cpp
 *
 *  Created on: Jan 27, 2013
 *      Author: cvangysel
 */

#include <iostream>

#include "zombieland.h"
#include "entity.h"

using std::cout;
using std::endl;

zl::Entity::Entity(Handler* handler, Region* region) : Object(handler), region(region), size(.25, .25), position(.5, .5), direction(0., 0.) {
}

zl::Entity::~Entity() {
}

void zl::Entity::process(Zombieland& game, unsigned int event) {
	Direction xAxisDirection = this->direction.first < 0 ? LEFT : RIGHT;
	Direction yAxisDirection = this->direction.second < 0 ? UP : DOWN;

	const Vector localMaxBound = Vector(1., 1.) - (this->size / 2);
	const Vector localMinBound = Vector(0., 0.) + (this->size / 2);

	auto transition = [this, &localMaxBound, &localMinBound](double Vector::*axis, Direction direction) {
		double min = localMinBound.*axis;
		double max = localMaxBound.*axis;

		bool increasing = direction == RIGHT || direction == DOWN;

		Region* nextRegion = this->region;

		double current = this->position.*axis;
		double next = current + this->direction.*axis;

		if ((next <= min && !increasing) || (next >= max && increasing)) {
			Region* adjacentRegion = nextRegion->getAdjacent(direction);

			if (adjacentRegion) {
				nextRegion = adjacentRegion;

				if (increasing) {
					next = next - 1.0;
				} else {
					next = 1.0 + next;
				}
			} else {
				if (increasing) {
					next = max;
				} else {
					next = min;
				}
			}
		}

		this->position.*axis = next;

		const Vector globalMinBound = this->region->getGlobalCoordinate(this->position - (this->size / 2));
		const Vector globalMaxBound = this->region->getGlobalCoordinate(this->position + (this->size / 2));

		bool collision = false;

		for (ObstacleList::const_iterator it = nextRegion->getObstacles().cbegin(); it != nextRegion->getObstacles().end(); it ++) {
			const Obstacle* obstacle = (*it);

			if (obstacle->intersects(globalMinBound, globalMaxBound)) {
				collision = true;

				break;
			}
		}

		if (!collision) {
			this->region = nextRegion;
		} else {
			this->position.*axis = current;
		}
	};

	transition(&Vector::first, xAxisDirection);
	transition(&Vector::second, yAxisDirection);

	zl::Object::process(game, event);
}

const zl::Region& zl::Entity::getRegion() const {
	return *this->region;
}

zl::Vector zl::Entity::getPosition() const {
	return this->region->getGlobalCoordinate(this->position);
}

zl::Vector zl::Entity::getSize() const {
	return Vector(this->size.first / this->region->getTerrain().getWidth(), this->size.second / this->region->getTerrain().getHeight());
}

void zl::Zombie::process(Zombieland& game, unsigned int event) {
	std::list<Direction> path;
	game.getTerrain().calculatePath(this->region, &game.getPlayer().getRegion(), path);

	if (path.size()) {
		switch (path.front()) {
		case UP:
			this->direction = Vector(.0, -.005);
			break;
		case RIGHT:
			this->direction = Vector(.005, .0);
			break;
		case DOWN:
			this->direction = Vector(.0, .005);
			break;
		case LEFT:
			this->direction = Vector(-.005, .0);
			break;
		default:
			this->direction = Vector(0., 0.);
			break;
		}
	} else {
		const Entity& player = game.getPlayer();

		this->direction = Vector(0., 0.);
	}

	zl::Entity::process(game, event);
}


void zl::Player::process(Zombieland& game, unsigned int event) {
	if (event & Event::MOVE_UP) {
		this->direction += Vector(.0, -.01);
	} else if (event & Event::MOVE_RIGHT) {
		this->direction += Vector(.01, .0);
	} else if (event & Event::MOVE_DOWN) {
		this->direction += Vector(.0, .01);
	} else if (event & Event::MOVE_LEFT) {
		this->direction += Vector(-.01, .0);
	}

	zl::Entity::process(game, event);
}
