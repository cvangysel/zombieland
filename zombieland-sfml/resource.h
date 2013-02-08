/*
 * resource.h
 *
 *  Created on: Feb 3, 2013
 *      Author: cvangysel
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <map>
#include <utility>
#include <typeinfo>
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;

namespace sfml {

	typedef std::pair<const std::type_info*, void*> Resource;

	class ResourceUnavailableException : std::exception {
	public:
		virtual const char* what() const throw() {
			return "The requested resource was not found.";
		}
	};

	enum ResourceIdentifier {
		SPRITE,
		SPRITE_LEFT,
		SPRITE_RIGHT,
		SPRITE_UP,
		SPRITE_DOWN
	};

	template <typename I>
	class Resources {
	public:
		virtual ~Resources() { };

		template <class T>
		T* getResource(I identifier) const {
			Resource resource;

			try {
				resource = this->handles.at(identifier);
			} catch (std::out_of_range& e) {
				throw ResourceUnavailableException();
			}

			void* ptr = resource.second;

			return reinterpret_cast<T*>(ptr);
		}
	protected:
		template <class T>
		void setResource(I identifier, T* resourcePointer) {
			Resource resource;

			resource.first = &typeid(resourcePointer);
			resource.second = resourcePointer;

			this->handles[identifier] = resource;
		}

		std::map<I, Resource> handles;
	};

	class GameResources : public Resources<ResourceIdentifier> {
	public:
		virtual ~GameResources();
	};

	class PlayerResources : public GameResources {
	public:
		PlayerResources();
	};

	template <int offset>
	class ZombieResources : public GameResources {
	public:
		ZombieResources() {
			{
				sf::Texture* texture = new sf::Texture();
				texture->loadFromFile("pacman.png", sf::IntRect(3, offset, 13, 13));
				this->setResource(SPRITE, texture);
			}

			{
				sf::Texture* texture = new sf::Texture();
				texture->loadFromFile("pacman.png", sf::IntRect(83, offset, 13, 13));
				this->setResource(SPRITE_LEFT, texture);
			}

			{
				sf::Texture* texture = new sf::Texture();
				texture->loadFromFile("pacman.png", sf::IntRect(123, offset, 13, 13));
				this->setResource(SPRITE_RIGHT, texture);
			}

			{
				sf::Texture* texture = new sf::Texture();
				texture->loadFromFile("pacman.png", sf::IntRect(3, offset, 13, 13));
				this->setResource(SPRITE_UP, texture);
			}

			{
				sf::Texture* texture = new sf::Texture();
				texture->loadFromFile("pacman.png", sf::IntRect(42, offset, 13, 13));
				this->setResource(SPRITE_DOWN, texture);
			}
		};
	};

	class RedZombieResources : public ZombieResources<83> { };

	class PinkZombieResources : public ZombieResources<102> { };

	class CyanZombieResources : public ZombieResources<122> { };

	class OrangeZombieResources : public ZombieResources<142> { };

}

#endif /* RESOURCE_H_ */
