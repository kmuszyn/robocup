/*
 * Geom.cpp
 *
 *  Created on: 2010-01-31
 *      Author: kamil
 */

#include "Geom.h"
#include "videoServer/VideoServer.h"
#include "config/AppConfig.h"

Geom::Geom() {
	// TODO Auto-generated constructor stub

}

Geom::~Geom() {
	// TODO Auto-generated destructor stub
}


bool Geom::isPathClear(Vector2d & start, Vector2d & end){


	std::map<std::string, Position2d*>::iterator ii =
			VideoServer::instance().data().begin();
	for (; ii != VideoServer::instance().data().end(); ii++) {
		//ball is skipped, collisions harmless
		if (ii->first == AppConfig::instance().ball) continue;
		//if start == obstacle pos - this is the robot the calculaction is done for, skip it
		if ((ii->second->pos - start).length() <  AppConfig::instance().radius) continue;
		//obstacle collides with path, return false
		if (ii->second->pos.distance(start, end) < 2 * AppConfig::instance().radius)
			return false;
	}
	return true;
}
