/*
 * graph.h
 *
 *  Created on: Jan 27, 2013
 *      Author: cvangysel
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <unordered_set>

#include "obstacle.h"

namespace zl {

	enum Direction {
		UP = 0,
		RIGHT = 1,
		DOWN = 2,
		LEFT = 3
	};

	Direction invert(Direction);

	class Region;
	class Terrain;

	typedef Region*** Graph;
	typedef std::unordered_set<const Obstacle*> ObstacleList;

	class Region {
	public:
		Region(const Terrain&, int x, int y);

		void connect(Direction, Region*);
		void disconnect();

		const std::unordered_set<const Obstacle*>& getObstacles() const;

		Region* getAdjacent(Direction) const;
		Region* const* getAdjacent() const;

		const Terrain& getTerrain() const;

		// TODO Remove these
		int getX() const;
		int getY() const;

		Vector getGlobalCoordinate(const Vector&) const;

		static Region* create(Terrain&, int, int);

		friend class Terrain;
	private:
		int x, y;
		Region* adjacent[4];
		const Terrain& terrain;

		ObstacleList obstacles;
	};

	class Terrain {
	public:
		Terrain(int, int, const std::list<const Obstacle*>&);
		~Terrain();

		Region* getStart();

		int getWidth() const;
		int getHeight() const;

		void calculatePath(const Region*, const Region*, std::list<Direction>&) const;
		Region* getPosition();

		friend class Region;
	private:
		Graph graph;

		int width;
		int height;
	};

}

#endif /* GRAPH_H_ */
