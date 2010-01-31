/*
 * Task.h
 *
 *  Created on: 2010-01-09
 *      Author: kamil
 */

#ifndef TASK_H_
#define TASK_H_

#include "robot/driver/Driver.h"

#include <string>

/**
 * Main class, defines robot task interface and task types.
 */
class Task {
public:
	Task();
	virtual ~Task();

	/**
	 * Executes task's actions
	 * @param d reference to robot's driver module
	 */
	virtual void execute(Driver & d) = 0;
	/**
	 * Is the task still vaild? (f.eg. position to go is occupied now)
	 *
	 * @return true if valid, false if invalid
	 */
	virtual bool valid() = 0;

	/**
	 * Informs if the task is complete so AI can end it.
	 *
	 * @return true if finished, false if not
	 */
	virtual bool finished() = 0;
	/**
	 * Returns the name of the task, may be useful for debugging
	 *
	 * @return name of the task
	 */
	virtual std::string getName() = 0;

	/**
	 * Return additional info about the task, useful for debugging
	 * F.eg. goTo task may return target position
	 */
	virtual std::string getInfo() = 0;
};

#endif /* TASK_H_ */
