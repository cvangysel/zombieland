/*
 * entity.cpp
 *
 *  Created on: Jan 27, 2013
 *      Author: cvangysel
 */

#include <iostream>
#include <utility>
#include <stdexcept>

#include "zombieland.h"
#include "entity.h"
#include "exceptions.h"
#include "rand.h"

using std::cout;
using std::endl;

zl::Entity::Entity(const Zombieland* game, Handler* handler, double velocity) :
		Object(handler), velocity(velocity), size(.25), direction(0.) {
	this->region = game->getTerrain().getRegion();

	this->position = Vector(
		rand(this->size.first, 1. - this->size.first),
		rand(this->size.second, 1. - this->size.second)
	);
}

zl::Entity::~Entity() { }

void zl::Entity::process(Zombieland& game, unsigned int event) {
	Vector move = normalize(this->direction) * this->velocity;

	std::pair<Direction, Direction> directions = move.getDirections();

	const Vector localMaxBound = Vector(1., 1.) - (this->size / 2);
	const Vector localMinBound = Vector(0., 0.) + (this->size / 2);

	auto transition = [this, &localMaxBound, &localMinBound, &move](double Vector::*axis, const Obstacle* Obstacles::*blocked, Direction direction) {
		if (direction == STATIONARY) {
			return false;
		}

		double min = localMinBound.*axis;
		double max = localMaxBound.*axis;

		bool increasing = direction == RIGHT || direction == DOWN;

		Region* nextRegion = this->region;

		double current = this->position.*axis;
		double next = current + move.*axis;

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
		this->blocked.*blocked = 0;

		const Vector globalMinBound = this->region->getGlobalCoordinate(this->position - (this->size / 2));
		const Vector globalMaxBound = this->region->getGlobalCoordinate(this->position + (this->size / 2));

		for (ObstacleList::const_iterator it = nextRegion->getObstacles().cbegin(); it != nextRegion->getObstacles().end(); it ++) {
			const Obstacle* obstacle = *it;

			if (obstacle->intersects(globalMinBound, globalMaxBound)) {
				this->position.*axis = current;
				this->blocked.*blocked = obstacle;

				break;
			}
		}

		this->region = nextRegion;
	};

	transition(&Vector::first, &Obstacles::first, directions.first);
	transition(&Vector::second, &Obstacles::second, directions.second);

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

zl::Direction zl::Entity::getDirection() const {
	std::pair<Direction, Direction> directions = this->direction.getDirections();

	return abs(this->direction.first) > abs(this->direction.second) ? directions.first : directions.second;
}

zl::Zombie::Zombie(const Zombieland* game, Handler* handler) : Entity(game, handler, .005) { }

void zl::Zombie::process(Zombieland& game, unsigned int event) {
	Direction playerDirection = STATIONARY;

	try {
		playerDirection = game.getPlayer().getDirection(this->region);

		this->direction = Vector(playerDirection);
	} catch (std::out_of_range& e) {
		this->direction = game.getPlayer().getPosition() - this->getPosition();
	}

	zl::Entity::process(game, event);
}

zl::Player::Player(const Zombieland* game, Handler* handler) : Entity(game, handler, .05) { }

void zl::Player::process(Zombieland& game, unsigned int event) {
	const list<Zombie*> zombies = game.getZombies();

	this->pathInformation.clear();

	for (list<Zombie*>::const_iterator it = zombies.cbegin(); it != zombies.end(); it ++) {
		this->region->getTerrain().calculatePath(&(*it)->getRegion(), this->region, this->pathInformation);
	}

	if (event & Event::MOVE_UP) {
		this->direction = Vector(0., - 1.);
	} else if (event & Event::MOVE_RIGHT) {
		this->direction = Vector(1., 0.);
	} else if (event & Event::MOVE_DOWN) {
		this->direction = Vector(0., 1.);
	} else if (event & Event::MOVE_LEFT) {
		this->direction = Vector(- 1., 0.);
	}

	zl::Entity::process(game, event);
}

zl::Direction zl::Player::getDirection(const Region* source) const {
	return this->pathInformation.at(source);
}
