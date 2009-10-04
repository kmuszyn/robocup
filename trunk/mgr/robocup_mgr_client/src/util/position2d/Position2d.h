/*
 * Position.h
 *
 *  Created on: 2009-05-06
 *      Author: kamil
 */

#ifndef POSITION_H_
#define POSITION_H_

#include "../vector2d/Vector2d.h"
#include "../angle/Angle.h"

class Position2d {
public:
	Vector2d pos;
	Angle rot;

	Position2d();
	Position2d(double x, double y, Angle rot);
	Position2d(const Position2d & );
	Position2d & operator=(const Position2d &);

	~Position2d();


};

#endif /* POSITION_H_ */
