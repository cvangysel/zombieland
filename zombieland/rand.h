/*
 * rand.h
 *
 *  Created on: Feb 1, 2013
 *      Author: cvangysel
 */

#ifndef RAND_H_
#define RAND_H_

#include <random>
#include <unordered_map>

namespace {

	int rand(int min, int max) {
		return ((double) std::rand() / ((double) RAND_MAX + 1.0)) * (max - min + 1) + min;
	}

	template <typename K, typename V>
	V rand(const std::unordered_map<K, V>& map) {
		typename std::unordered_map<K, V>::const_iterator it = map.cbegin();
		std::advance(it, rand(0, map.size()));

		return it->second;
	}

	template <typename T>
	const T* rand(const T* array, int max) {
		return array + (std::rand() % max);
	}

	double rand(double min, double max) {
		return ((static_cast<double>(std::rand()) / RAND_MAX) * (max - min)) + min;
	}

}

#endif /* RAND_H_ */
