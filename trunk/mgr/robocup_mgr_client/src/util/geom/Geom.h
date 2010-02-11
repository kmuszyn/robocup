/*
 * Geom.h
 *
 *  Created on: 2010-01-31
 *      Author: kamil
 */

#ifndef GEOM_H_
#define GEOM_H_

#include "util/vector2d/Vector2d.h"

/**
 * Geom class provides methods to perform basic geometry calculations, f.eg. checking if
 * given path is obstacle-free.
 *
 */
class Geom {
public:
	Geom();
	~Geom();

public:
	/**
	 * Checks if path from start to end is obstacle-free.
	 * List of obstacles based on VideoData.
	 * Warning: start point usually is a robot's position, so
	 * if obstacle and start position is closer then robot radious,
	 * it is assumed that this is the robot we are doing calculation for.
	 *
	 * @return true if path is clear
	 */
	static bool isPathClear(Vector2d & start, Vector2d & end);
};

#endif /* GEOM_H_ */
