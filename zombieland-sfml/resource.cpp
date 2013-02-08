/*
 * resource.cpp
 *
 *  Created on: Feb 3, 2013
 *      Author: cvangysel
 */

#include <iostream>

#include <SFML/Graphics.hpp>

#include "resource.h"

using std::cout;
using std::endl;

sfml::GameResources::~GameResources() {
	delete this->handles[SPRITE].second;
	delete this->handles[SPRITE_LEFT].second;
	delete this->handles[SPRITE_RIGHT].second;
	delete this->handles[SPRITE_UP].second;
	delete this->handles[SPRITE_DOWN].second;
}

sfml::PlayerResources::PlayerResources() {
	{
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile("pacman.png", sf::IntRect(43, 3, 13, 13));
		this->setResource(SPRITE, texture);
	}

	{
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile("pacman.png", sf::IntRect(3, 3, 13, 13));
		this->setResource(SPRITE_LEFT, texture);
	}

	{
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile("pacman.png", sf::IntRect(3, 23, 13, 13));
		this->setResource(SPRITE_RIGHT, texture);
	}

	{
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile("pacman.png", sf::IntRect(3, 43, 13, 13));
		this->setResource(SPRITE_UP, texture);
	}

	{
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile("pacman.png", sf::IntRect(3, 63, 13, 13));
		this->setResource(SPRITE_DOWN, texture);
	}
}
