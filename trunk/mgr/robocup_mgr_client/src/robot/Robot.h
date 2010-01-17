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
	/**
	 * Robot constructor, inits model name and team, to which robot belongs
	 */
	Robot(std::string modelName, TeamName team);
	~Robot();


	void go();

	/**
	 * Go to position action.
	 *
	 * @param pos position to go to
	 */
	void goTo(Position2d & pos);

	void doTest();

#ifdef MGR_VIEWER
	void writeViewerData();
#endif

///////////////////////////////////////////////////////////////////////////////////////
private:
	///Robot's team
	TeamName team;

	///name of a model
	std::string modelName;

	///This robot driver - physical layer
	Driver driver;

	///Waypoints, temporary here
	std::stack<Position2d *> waypoints;

	static log4cxx::LoggerPtr logger;
};

#endif /* ROBOT_H_ */
