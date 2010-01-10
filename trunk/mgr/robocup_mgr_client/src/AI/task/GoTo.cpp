/*
 * GoTo.cpp
 *
 *  Created on: 2010-01-10
 *      Author: kamil
 */

#include "GoTo.h"

GoTo::GoTo(Robot & robot, Position2d position) : robot(robot), position(position), taskName("GoTo") {


}

GoTo::~GoTo() {

}

void GoTo::execute(){
	robot.goTo(position);
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
