/*
 * handler.cpp
 *
 *  Created on: Jan 27, 2013
 *      Author: cvangysel
 */

#include <iostream>
#include <cmath>

#include "handler.h"

using std::cout;
using std::endl;

void sfml::updateSprite(const sf::Vector2u& windowSize, sf::Sprite& sprite, const zl::Object& object) {
	zl::Vector size = object.getSize();

	int width = floor(size.first * windowSize.x);
	int height = floor(size.second * windowSize.y);

	sprite.setTextureRect(sf::IntRect(0, 0, width, height));

	zl::Vector position = object.getPosition();

	int x = position.first * windowSize.x - (.5 * width);
	int y = position.second * windowSize.y - (.5 * height);

	sprite.setPosition(x, y);
}

sfml::Handler::~Handler() {
	delete this->sprite;
}

sfml::EntityHandler::EntityHandler(sf::RenderWindow& window) : sfml::Handler(window) {
	this->sprite = new sf::Sprite();

	sf::Texture texture;
	//texture.loadFromFile("sprite.png");

	this->sprite->setTexture(texture);
	this->sprite->setColor(sf::Color(255, 255, 255, 200));
}

void sfml::EntityHandler::handle(zl::Zombieland& game, const zl::Object& object) {
	sf::Vector2u windowSize = this->window.getSize();
	updateSprite(windowSize, *this->sprite, object);

	this->window.draw(*this->sprite);
}

sfml::ObstacleHandler::ObstacleHandler(sf::RenderWindow& window) : sfml::Handler(window) { }

void sfml::ObstacleHandler::handle(zl::Zombieland& game, const zl::Object& object) {
	if (!this->sprite) {
		this->sprite = new sf::Sprite();

		sf::Texture texture;
		//texture.loadFromFile("sprite.png");

		this->sprite->setTexture(texture);
		this->sprite->setColor(sf::Color(255, 255, 255, 200));

		sf::Vector2u windowSize = this->window.getSize();
		updateSprite(windowSize, *this->sprite, object);
	}

	this->window.draw(*this->sprite);
}
