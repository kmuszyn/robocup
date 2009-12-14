/*
 * Position.cpp
 *
 *  Created on: 2009-05-06
 *      Author: kamil
 */

#include "Position2d.h"



/////////////////////////// konstruktory //////////////////////////

Position2d::Position2d() : rot() {

}

Position2d::Position2d(const Position2d & pos2d) {
	this->pos = pos2d.pos;
	this->rot = pos2d.rot;
}

Position2d::Position2d(double x, double y, Angle rot){
	this->pos.x = x;
	this->pos.y = y;
	this->rot = rot;
}

Position2d & Position2d::operator=(const Position2d & pos2d){
	this->pos = pos2d.pos;
	this->rot = pos2d.rot;
	return *this;
}

////////////////////////////////////////////////////////////////////

Position2d::~Position2d() {
	//empty
}

std::ostream & operator<<(std::ostream & os, const Position2d & v ){
	os<<v.pos<<", rot: "<<v.rot.val;
	return os;
}
