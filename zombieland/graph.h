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
#include <unordered_map>

#include "obstacle.h"
#include "utils.h"

namespace zl {

	class Region;
	class Terrain;

	typedef Region*** Graph;
	typedef std::unordered_set<const Obstacle*> ObstacleList;

	typedef std::unordered_map<const Region*, Direction> PathInformation;

	class Region {
	public:
		Region(const Terrain&, int x, int y);

		void connect(Direction, Region*);
		void disconnect();

		const std::unordered_set<const Obstacle*>& getObstacles() const;
		bool contains(const Obstacle*) const;

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

		void calculatePath(const Region*, const Region*, PathInformation&) const;

		Region* getRegion(bool = true) const;

		friend class Region;
	private:
		Graph graph;

		int width;
		int height;
	};

}

#endif /* GRAPH_H_ */
