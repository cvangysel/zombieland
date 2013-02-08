/*
 * factory.cpp
 *
 *  Created on: Jan 27, 2013
 *      Author: cvangysel
 */

#include "zombieland/rand.h"

#include "factory.h"
#include "handler.h"

sfml::Factory::Factory(sf::RenderWindow& window) : window(window) {
	this->zombieResources[0] = new RedZombieResources();
	this->zombieResources[1] = new PinkZombieResources();
	this->zombieResources[2] = new OrangeZombieResources();
	this->zombieResources[3] = new CyanZombieResources();
}

sfml::Factory::~Factory() {
	for (int i = 0; i < 4; i ++) {
		delete this->zombieResources[i];
	}
}

zl::Zombie* sfml::Factory::createZombie(const zl::Zombieland* game) {
	return new zl::Zombie(game, new sfml::EntityHandler(this->window, **rand(this->zombieResources, 4)));
}

zl::Player* sfml::Factory::createPlayer(const zl::Zombieland* game) {
	return new zl::Player(game, new sfml::EntityHandler(this->window, this->playerResources));
}

zl::Block* sfml::Factory::createBlock(const zl::Vector& position, const zl::Vector& size) {
	return new zl::Block(new sfml::ObstacleHandler(this->window, this->obstacleResources), position, size);
}
