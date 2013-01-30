/*
 * zombieland.cpp
 *
 *  Created on: Jan 27, 2013
 *      Author: cvangysel
 */

#include <iostream>

#include "zombieland.h"

using std::cout;
using std::endl;

zl::Zombieland::Zombieland(Factory& factory, int width, int height) : factory(factory) {
	std::list<const Obstacle*> obstacles;

	Obstacle* obstacle = factory.createBlock(Vector(.75, .45), Vector(.55, .2));
	this->objects.push_back(obstacle);
	obstacles.push_back(obstacle);

	this->terrain = new Terrain(width, height, obstacles);

	this->player = factory.createPlayer(this->terrain->getStart());

	for (int i = 0; i < 5; i ++) {
		this->objects.push_back(factory.createZombie(this->terrain->getPosition()));
	}

	this->objects.push_back(this->player);
}

zl::Zombieland::~Zombieland() {
	for (list<Object*>::iterator it = this->objects.begin(); it != this->objects.end(); it++) {
		delete (*it);
	}

	delete this->terrain;
}

void zl::Zombieland::tick(unsigned int event) {
	for (list<Object*>::iterator it = this->objects.begin(); it != this->objects.end(); it++) {
		(*it)->process(*this, event);
	}
}

const zl::Terrain& zl::Zombieland::getTerrain() const {
	return *this->terrain;
}

const zl::Entity& zl::Zombieland::getPlayer() const {
	return *this->player;
}
