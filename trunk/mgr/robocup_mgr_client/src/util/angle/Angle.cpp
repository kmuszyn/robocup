/*
 * Angle.cpp
 *
 *  Created on: 2009-05-09
 *      Author: kamil
 */

#include "Angle.h"

Angle Angle::operator-(const Angle & a){
	//założenie, że kąty są poprawne, tj w przedziale -PI..PI
	double res = this->val - a.val;
	res = correctAngle(res);
	return Angle(res);
}

double Angle::correctAngle(double angle){
	double _2M_PI = 2 * M_PI;

	if (angle > M_PI){
		angle = _2M_PI - angle;
	}
	else if (angle<-M_PI){
		angle = _2M_PI + angle;
	}

	return angle;
}



double Angle::degreeValue(){
	return this->val * (180.0 / M_PI);
}

////////////////////////////////////////////////////////////////////////

Angle::Angle() {
	this->val = 0.0;
}

Angle::Angle(double val){
	this->val = val;
}

Angle::Angle(const Angle & a){
	this->val = a.val;
}
Angle & Angle::operator=(const Angle & a){
	this->val = a.val;
	return *this;
}

Angle::~Angle() {
	//empty
}
