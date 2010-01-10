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
	pos = pos2d.pos;
	rot = pos2d.rot;
	dX = pos2d.dX;
	dY = pos2d.dY;
	dRot = pos2d.dRot;
}

Position2d::Position2d(double x, double y, Angle rot){
	pos.x = x;
	pos.y = y;
	rot = rot;
}

Position2d & Position2d::operator=(const Position2d & pos2d){
	pos = pos2d.pos;
	rot = pos2d.rot;
	dX = pos2d.dX;
	dY = pos2d.dY;
	dRot = pos2d.dRot;
	return *this;
}

void Position2d::update(Position2d & newPos)
{
	//calculate differences
	dX = newPos.pos.x - pos.x;
	dY = newPos.pos.y - pos.y;
	dRot = newPos.rot.val - rot.val;	//TODO: check if this is ok with angle wrapping...
	//copy
	pos = newPos.pos;
	rot = newPos.rot;
}

////////////////////////////////////////////////////////////////////

Position2d::~Position2d() {
	//empty
}

std::ostream & operator<<(std::ostream & os, const Position2d & v ){
	os<<v.pos<<", rot: "<<v.rot.val<<" d:("<<v.dX<<","<<v.dY<<" "<<v.dRot<<")";
	return os;
}
