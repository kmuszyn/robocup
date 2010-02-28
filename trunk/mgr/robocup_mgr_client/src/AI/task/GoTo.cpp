/*
 * GoTo.cpp
 *
 *  Created on: 2010-01-10
 *      Author: kamil
 */

#include "GoTo.h"
#include "robot/RRT/RRT2.h"
#include "util/geom/Geom.h"

GoTo::GoTo(Position2d dest, const string & robotName) :
	dest(dest), robotName(robotName), taskName("GoTo") {

}

GoTo::~GoTo() {

}

void GoTo::execute(Driver & driver){

	Position2d * robotPos = (VideoServer::instance().data())[driver.getModelName()];

	RRT2 rrt(robotName);
	Vector2d tmp;
	rrt.plan(this->dest.pos, tmp);
	Position2d tmpPos;
	tmpPos.pos = tmp;
	tmpPos.rot = this->dest.rot;

	driver.goToPosition(&tmpPos);
}


bool GoTo::valid(){
	//Vector2d robotPos;

	list<Vector2d> obstacles;
	std::map<std::string, Position2d*>::iterator ii =
			VideoServer::instance().data().begin();
	for (; ii != VideoServer::instance().data().end(); ii++) {
		if (ii->first == AppConfig::instance().ball) continue;
		if (ii->first == robotName){
			//robotPos = ii->second->pos;
			continue;
		}
		obstacles.push_back(ii->second->pos);
//		cout<<"Adding: "<<ii->second->pos<<endl;
	}

	return !Geom::pointCollides(dest.pos, obstacles);
}

bool GoTo::finished(){
	Position2d * robotPos = (VideoServer::instance().data())[robotName];



	if ( (robotPos->pos - dest.pos).length() < 0.05){
		std::cout<<"Task finished\n";
		return true;
	}

	return false;
}

std::string GoTo::getName(){
	return taskName;
}

std::string GoTo::getInfo(){
	std::ostringstream outs;
	outs<<dest.pos.x<<" "<<dest.pos.y<<" "<<dest.rot.degreeValue();
	return outs.str();
}
