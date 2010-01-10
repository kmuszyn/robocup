/*
 * AI.h
 *
 *  Created on: 2010-01-10
 *      Author: kamil
 */

#ifndef AI_H_
#define AI_H_

#include <string>

#include <robot/Robot.h>
#include <util/types.h>
#include <AI/task/Task.h>

/**
 * Represents artificial intelligence that controls it's own robot in a game
 *
 */
class AI {
public:
	/**
	 * Constructor of AI
	 *
	 * @param robotName Name of the robot model in gazebo to control
	 * @param teamName team to which controlled robot belongs
	 */
	AI(std::string robotName, TeamName teamName);

	/**
	 * Destructor, clears tasks
	 */
	~AI();

	/**
	 * Main AI method, performs tasks selection and execution
	 *
	 */
	void act();

////////////////////////////////////////////////////////////////////////////////////
private:
	/**
	 * Generates new task for a robot
	 */
	void generateTask();

////////////////////////////////////////////////////////////////////////////////////
private:
	///Robot controlled by AI
	Robot robot;
	///Robot's task
	Task * task;
};

#endif /* AI_H_ */
