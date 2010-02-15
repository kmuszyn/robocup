/*
 * Geom.h
 *
 *  Created on: 2010-01-31
 *      Author: kamil
 */

#ifndef GEOM_H_
#define GEOM_H_

#include "util/vector2d/Vector2d.h"
#include <list>
#include <string>

/**
 * Geom class provides methods to perform basic geometry calculations, f.eg. checking if
 * given path is obstacle-free.
 *
 */
using namespace std;

class Geom {
public:
	Geom();
	~Geom();

public:
	/**
	 * Checks if path from start to end is obstacle-free.
	 *
	 * @return true if path is clear
	 */
	static bool isPathClear(const Vector2d & start, const Vector2d & end, const list<Vector2d> & obstacles);

	/**
	 * Checks if point collides with given robot positions
	 */
	static bool pointCollides(const Vector2d & point, const list<Vector2d> & obstacles);
};

#endif /* GEOM_H_ */
