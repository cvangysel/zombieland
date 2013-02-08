/*
 * zombieland.cpp
 *
 *  Created on: Jan 27, 2013
 *      Author: cvangysel
 */

#include <iostream>

#include "zombieland.h"
#include "rand.h"

using std::cout;
using std::endl;

zl::Zombieland::Zombieland(Factory& factory, int width, int height) : factory(factory) {
	std::list<const Obstacle*> obstacles;

	this->placeBlock(Vector(.40, .30), Vector(.60, .3));
	this->placeBlock(Vector(.25, .75), Vector(.2, .2));
	this->placeBlock(Vector(.75, .75), Vector(.2, .2));

	this->terrain = new Terrain(width, height, this->obstacles);

	this->player = factory.createPlayer(this);
	this->objects.push_back(this->player);
}

zl::Zombieland::~Zombieland() {
	for (list<Object*>::iterator it = this->objects.begin(); it != this->objects.end(); it++) {
		delete (*it);
	}

	delete this->terrain;
}

void zl::Zombieland::tick(unsigned int event) {
	double randomness = rand(0., 1.);
	if (randomness <= .01) {
		this->spawnZombie();
	}

	for (list<Object*>::iterator it = this->objects.begin(); it != this->objects.end(); it++) {
		(*it)->process(*this, event);
	}
}

const zl::Terrain& zl::Zombieland::getTerrain() const {
	return *this->terrain;
}

const zl::Player& zl::Zombieland::getPlayer() const {
	return *this->player;
}

const list<zl::Zombie*>& zl::Zombieland::getZombies() const {
	return this->zombies;
}

void zl::Zombieland::placeBlock(Vector position, Vector size) {
	Obstacle* obstacle = factory.createBlock(position, size);

	this->objects.push_back(obstacle);
	this->obstacles.push_back(obstacle);
}

void zl::Zombieland::spawnZombie() {
	Zombie* zombie = factory.createZombie(this);

	this->objects.push_back(zombie);
	this->zombies.push_back(zombie);
}
