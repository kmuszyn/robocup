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
#include "AI/AI.h"

#include <iostream>
#include <string>

#include "log4cxx/logger.h"


class AI;

/**
 * Class Robot represents and controls single robot model in gazebo simulation.
 *
 */
class Robot {
public:
	/**
	 * Robot constructor, inits model name and team, to which robot belongs
	 */
	Robot(std::string name, TeamName team);
	~Robot();

	/**
	 * Main method for robot controlling, performs AI planning and robot actions.
	 */
	void makeMove();

#ifdef MGR_VIEWER
	void writeViewerData(RRT & rrt);
#endif

///////////////////////////////////////////////////////////////////////////////////////
private:
	///Robot's team
	TeamName team;

	///name of a model
	std::string name;

	///This robot driver - physical layer
	Driver driver;

	///AI algorithms to control robot
	AI ai;


	static log4cxx::LoggerPtr logger;
};

#endif /* ROBOT_H_ */
