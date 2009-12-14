/*
 * Robot.h
 *
 *  Created on: 2009-05-04
 *      Author: kamil
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "util/types.h"
#include "util/position2d/Position2d.h"
#include "robot/driver/Driver.h"
#include "robot/RRT/RRTTree.h"
#include "robot/RRT/RRT.h"

#include <string>
#include <stack>
#include "log4cxx/logger.h"


/**
 * Class Robot represents and controls single robot model in gazebo simulation.
 *
 */
class Robot {
public:
	Robot(std::string modelName, TeamName team);
	~Robot();

	void go();

	void doTest();

///////////////////////////////////////////////////////////////////////////////////////
private:
	TeamName team;
	std::string modelName;
	Driver driver;

	std::stack<Position2d *> waypoints;

	static log4cxx::LoggerPtr logger;
};

#endif /* ROBOT_H_ */
