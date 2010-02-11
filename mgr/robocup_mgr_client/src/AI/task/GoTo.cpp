/*
 * GoTo.cpp
 *
 *  Created on: 2010-01-10
 *      Author: kamil
 */

#include "GoTo.h"
#include "robot/RRT/RRT.h"
#include "util/geom/Geom.h"

GoTo::GoTo(Position2d position) :  position(position), taskName("GoTo") {


}

GoTo::~GoTo() {

}

void GoTo::execute(Driver & d){

	Position2d * robotPos = (VideoServer::instance().data())[d.getModelName()];

	if (Geom::isPathClear(robotPos->pos, this->position.pos)){
		std::cout<<".";
		d.goToPosition(&(this->position));
	}
	else{
		RRT rrt(d.getModelName());
		Vector2d tmp = rrt.plan(this->position.pos);
		Position2d tmpPos;
		tmpPos.pos = tmp;
		tmpPos.rot = this->position.rot;

		d.goToPosition(&tmpPos);
	}
}

bool GoTo::valid(){
	return true;
}

bool GoTo::finished(){
	return false;
}

std::string GoTo::getName(){
	return taskName;
}

std::string GoTo::getInfo(){
	std::ostringstream outs;
	outs<<position.pos.x<<" "<<position.pos.y<<" "<<position.rot.degreeValue();
	return outs.str();
}
