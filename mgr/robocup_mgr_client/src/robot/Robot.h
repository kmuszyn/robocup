/*
 * Robot.h
 *
 *  Created on: 2009-05-04
 *      Author: kamil
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "../util/types.h"
#include "../gameState/GameState.h"
#include "driver/Driver.h"
#include "RRT/RRTTree.h"
#include "RRT/RRT.h"

#include <string>
#include "log4cxx/logger.h"

class Robot {
public:
	Robot(std::string modelName, TeamName team, GameState * gameState);
	~Robot();

	void doTest();
private: /******************************************/
	TeamName team;
	std::string modelName;
	GameState * gameStatePtr;
	Driver driver;

	static log4cxx::LoggerPtr logger;
};

#endif /* ROBOT_H_ */
