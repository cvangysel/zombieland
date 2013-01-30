/*
 * utils.h
 *
 *  Created on: Jan 28, 2013
 *      Author: cvangysel
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <random>
#include <unordered_map>
#include <iterator>

#include "utils.h"

namespace zl {

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

}

#endif /* UTILS_H_ */
