/*
 * factory.cpp
 *
 *  Created on: Jan 27, 2013
 *      Author: cvangysel
 */

#include "factory.h"
#include "handler.h"

zl::Zombie* sfml::Factory::createZombie(zl::Region* region) {
	return new zl::Zombie(new sfml::EntityHandler(this->window), region);
}

zl::Player* sfml::Factory::createPlayer(zl::Region* region) {
	return new zl::Player(new sfml::EntityHandler(this->window), region);
}

zl::Block* sfml::Factory::createBlock(const zl::Vector& position, const zl::Vector& size) {
	return new zl::Block(new sfml::ObstacleHandler(this->window), position, size);
}
