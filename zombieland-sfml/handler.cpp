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

	const sf::IntRect& textureRect = sprite.getTextureRect();

	float width = floor(size.first * windowSize.x);
	float height = floor(size.second * windowSize.y);

	if (textureRect.width > 0 && textureRect.height > 0) {
		float scaleX = width / textureRect.width;
		float scaleY = height / textureRect.height;

		sprite.setScale(scaleX, scaleY);
	} else {
		sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	}

	zl::Vector position = object.getPosition();

	int x = position.first * windowSize.x - (.5 * width);
	int y = position.second * windowSize.y - (.5 * height);

	sprite.setPosition(x, y);
}

sfml::Handler::~Handler() {
	delete this->sprite;
}

sfml::EntityHandler::EntityHandler(sf::RenderWindow& window, const sfml::Resources<ResourceIdentifier>& resources) : sfml::Handler(window, resources) {
	this->sprite = 0;

	try {
		sf::Texture* texture = resources.getResource<sf::Texture>(SPRITE);

		this->sprite = new sf::Sprite(*texture);
	} catch (ResourceUnavailableException& e) {
		this->sprite = new sf::Sprite();
		this->sprite->setTexture(sf::Texture());
	}
}

void sfml::EntityHandler::handle(zl::Zombieland& game, const zl::Object& object) {
	try {
		sf::Texture* texture = 0;

		switch (object.getDirection()) {
		case zl::UP:
			texture = resources.getResource<sf::Texture>(SPRITE_UP);
			break;
		case zl::RIGHT:
			texture = resources.getResource<sf::Texture>(SPRITE_RIGHT);
			break;
		case zl::DOWN:
			texture = resources.getResource<sf::Texture>(SPRITE_DOWN);
			break;
		case zl::LEFT:
			texture = resources.getResource<sf::Texture>(SPRITE_LEFT);
			break;
		default:
			texture = resources.getResource<sf::Texture>(SPRITE);
			break;
		}

		this->sprite->setTexture(*texture);
	} catch (ResourceUnavailableException& e) {
	}

	sf::Vector2u windowSize = this->window.getSize();
	updateSprite(windowSize, *this->sprite, object);

	this->window.draw(*this->sprite);
}

sfml::ObstacleHandler::ObstacleHandler(sf::RenderWindow& window, const sfml::Resources<ResourceIdentifier>& resources) : sfml::Handler(window, resources) {

}

void sfml::ObstacleHandler::handle(zl::Zombieland& game, const zl::Object& object) {
	if (!this->sprite) {
		this->sprite = new sf::Sprite();

		sf::Texture texture;

		this->sprite->setTexture(texture);
		this->sprite->setColor(sf::Color(255, 255, 255, 200));

		sf::Vector2u windowSize = this->window.getSize();
		updateSprite(windowSize, *this->sprite, object);
	}

	this->window.draw(*this->sprite);
}
