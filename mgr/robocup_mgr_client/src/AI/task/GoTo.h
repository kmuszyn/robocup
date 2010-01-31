/*
 * GoTo.h
 *
 *  Created on: 2010-01-10
 *      Author: kamil
 */

#ifndef GOTO_H_
#define GOTO_H_

#include "Task.h"
#include "robot/Robot.h"
#include "util/position2d/Position2d.h"

#include <string>

/**
 * Go to given position (x,y,rot)
 */
class GoTo: public Task {
public:
	/**
	 * Constructor
	 *
	 * @param position target position for a robot
	 */
	GoTo(Position2d position);
	~GoTo();

	void execute(Driver & d);

	bool valid();
	bool finished();

	std::string getName();

	std::string getInfo();
////////////////////////////////////////////////////////////////////
private:
	///Go to position
	Position2d position;

	///Task name
	std::string taskName;
};

#endif /* GOTO_H_ */
