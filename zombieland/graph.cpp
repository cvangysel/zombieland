/*
 * graph.cpp
 *
 *  Created on: Jan 28, 2013
 *      Author: cvangysel
 */

#include <assert.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <algorithm>

#include "utils.h"
#include "graph.h"
#include "object.h"

using std::cout;
using std::endl;
using std::min;

zl::Direction zl::invert(Direction direction) {
	switch (direction) {
	case UP:
		return DOWN;
	case DOWN:
		return UP;
	case LEFT:
		return RIGHT;
	case RIGHT:
		return LEFT;
	}
}

zl::Region* zl::Region::create(Terrain& terrain, int x, int y) {
	if (x < 0 || y < 0) {
		return 0;
	}

	Graph& graph = terrain.graph;

	if (graph[x][y] == 0) {
		graph[x][y] = new Region(terrain, x, y);

		Region* node = graph[x][y];

		if (Region* left = Region::create(terrain, x - 1, y)) {
			node->connect(LEFT, left);
		}

		if (Region* down = Region::create(terrain, x, y - 1)) {
			node->connect(UP, down);
		}
	}

	return graph[x][y];
}

zl::Region::Region(const Terrain& terrain, int x, int y) : x(x), y(y), adjacent({0, 0, 0, 0}), terrain(terrain)  { }

void zl::Region::connect(Direction direction, Region* neighbour) {
	assert(neighbour != 0);
	assert(this->adjacent[direction] == 0);
	assert(neighbour->adjacent[invert(direction)] == 0);

	this->adjacent[direction] = neighbour;
	neighbour->adjacent[invert(direction)] = this;

	assert(this->adjacent[direction] != 0);
	assert(neighbour->adjacent[invert(direction)] != 0);
}

void zl::Region::disconnect() {
	for (int i = 0; i < 4; i ++) {
		if (this->adjacent[i]) {
			this->adjacent[i]->adjacent[invert(Direction(i))] = 0;
			this->adjacent[i] = 0;
		}
	}
}

const std::unordered_set<const zl::Obstacle*>& zl::Region::getObstacles() const {
	return this->obstacles;
}

zl::Region* zl::Region::getAdjacent(Direction direction) const {
	return this->adjacent[direction];
}

zl::Region* const* zl::Region::getAdjacent() const {
	return this->adjacent;
}

const zl::Terrain& zl::Region::getTerrain() const {
	return this->terrain;
}

int zl::Region::getX() const {
	return this->x;
}

int zl::Region::getY() const {
	return this->y;
}

zl::Vector zl::Region::getGlobalCoordinate(const zl::Vector& vector) const {
	return Vector(
		(this->x + vector.first) / this->terrain.getWidth(),
		(this->y + vector.second) / this->terrain.getHeight()
	);
}

zl::Terrain::Terrain(int width, int height, const std::list<const Obstacle*>& obstacles) : width(width), height(height) {
	assert(width > 0);
	assert(height > 0);

	this->graph = new Region**[width];
	for (int x = 0; x < width; x ++) {
		this->graph[x] = new Region*[width];

		for (int y = 0; y < height; y ++) {
			this->graph[x][y] = 0;
		}
	}

	Region::create(*this, height - 1, width - 1);

	for (std::list<const Obstacle*>::const_iterator it = obstacles.begin(); it != obstacles.end(); it ++) {
		const Obstacle* obstacle = *it;

		Vector leftBounds = obstacle->getPosition() - (obstacle->getSize() / 2);
		Vector rightBounds = obstacle->getPosition() + (obstacle->getSize() / 2);

		{
			int leftX = ceil(leftBounds.first * this->width);
			int leftY = ceil(leftBounds.second * this->height);

			int rightX = floor(rightBounds.first * this->width);
			int rightY = floor(rightBounds.second * this->height);

			for (int x = leftX; x < rightX; x ++) {
				for (int y = leftY; y < rightY; y ++) {
					this->graph[x][y]->disconnect();
					delete this->graph[x][y];

					this->graph[x][y] = 0;
				}
			}
		}

		{
			auto addObstacle = [this, obstacle](int x, int y) {
				if (this->graph[x][y] != 0) {
					this->graph[x][y]->obstacles.insert(obstacle);
				}
			};

			int leftX = min(static_cast<int>(floor(leftBounds.first * this->width)), this->width);
			int leftY = min(static_cast<int>(floor(leftBounds.second * this->height)), this->height);

			int rightX = min(static_cast<int>(ceil(rightBounds.first * this->width)), this->width);
			int rightY = min(static_cast<int>(ceil(rightBounds.second * this->height)), this->height);

			for (int x = leftX; x < rightX; x ++) {
				addObstacle(x, leftY);
				addObstacle(x, rightY - 1);
			}

			for (int y = leftY; y < rightY; y ++) {
				addObstacle(leftX, y);
				addObstacle(rightX - 1, y);
			}
		}
	}
}

zl::Terrain::~Terrain() {
	for (int x = 0; x < width; x ++) {
		for (int y = 0; y < height; y ++) {
			delete this->graph[x][y];
		}

		delete [] this->graph[x];
	}

	delete [] this->graph;
}

zl::Region* zl::Terrain::getStart() {
	for (int x = 0; x < this->width; x ++) {
		for (int y = 0; y < this->height; y ++) {
			if (this->graph[x][y] != 0) {
				return this->graph[x][y];
			}
		}
	}
}

int zl::Terrain::getWidth() const {
	return this->width;
}

int zl::Terrain::getHeight() const {
	return this->height;
}

void zl::Terrain::calculatePath(const Region* begin, const Region* end, std::list<Direction>& path) const {
	std::list<const Region*> queue;
	std::unordered_set<const Region*> visited;
	std::unordered_map<const Region*, std::pair<const Region*, Direction>> previous;

	queue.push_back(begin);

	while (!queue.empty()) {
		const Region* node = queue.front();
		queue.pop_front();

		if (node == end) {
			while (previous.find(node) != previous.end()) {
				path.push_front(previous[node].second);
				node = previous[node].first;
			}

			return;
		}

		visited.insert(node);

		Region* const* adjacent = node->getAdjacent();

		for (int i = 0; i < 4; i ++) {
			Region* child = 0;

			if ((child = *(adjacent + i)) && (visited.find(child) == visited.end())) {
				queue.push_back(child);

				previous[child] = std::pair<const Region*, Direction>(node, Direction(i));
			}
		}
	}
}

zl::Region* zl::Terrain::getPosition() {
	return *rand(*rand(this->graph, this->width), this->height);
}
