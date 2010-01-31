/*
 * GoTo.cpp
 *
 *  Created on: 2010-01-10
 *      Author: kamil
 */

#include "GoTo.h"

GoTo::GoTo(Position2d position) :  position(position), taskName("GoTo") {


}

GoTo::~GoTo() {

}

void GoTo::execute(Driver & d){
	d.goToPosition(&position);
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
