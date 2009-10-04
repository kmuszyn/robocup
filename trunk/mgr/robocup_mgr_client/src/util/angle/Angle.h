/*
 * Angle.h
 *
 *  Created on: 2009-05-09
 *      Author: kamil
 */

#ifndef ANGLE_H_
#define ANGLE_H_

#include <math.h>

/**
 * Klasa reprezentująca kąt wyrażony w radianach(!),
 * pozwala na operacje na kątach z zawijaniem do -PI...PI
 * (tak jak w gazebo).
 */

class Angle {
public:
///////////////////
	double val;////
///////////////////

//////////////////////////////////////////////
	Angle();								//
	Angle(double val);						//
	Angle(const Angle & );					//
	Angle & operator=(const Angle & );		//
	~Angle();								//
//////////////////////////////////////////////

	Angle operator-(const Angle &);
	double degreeValue();
	double correctAngle(double angle);	//zawija do -PI..PI



};

#endif /* ANGLE_H_ */
