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

using namespace std;

/**
 * Go to given position (x,y,rot)
 */
class GoTo: public Task {
public:
	/**
	 * Constructor
	 *
	 * @param dest target position for a robot
	 * @param modelName robot model name
	 */
	GoTo(Position2d dest, const string & robotName);
	~GoTo();

	void execute(Driver & d);

	bool valid();
	bool finished();

	std::string getName();

	std::string getInfo();
////////////////////////////////////////////////////////////////////
private:
	///Go to position
	Position2d dest;

	///Task name
	std::string taskName;

	//Driver ref
	const string & robotName;
};

#endif /* GOTO_H_ */
