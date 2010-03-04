/*
 * Driver.h
 *
 *  Created on: 2009-05-04
 *      Author: kamil
 */

#ifndef DRIVER_H_
#define DRIVER_H_

#include "log4cxx/logger.h"
#include <string>
#include <deque>
#include <gazebo.h>

#include "simControl/SimControl.h"
#include "util/position2d/Position2d.h"


class Driver {
public:
	Driver(std::string modelName);
	~Driver();

	///Metoda aktualizująca parametry używane przez sterownik - prędkości liniową i kątową
	void updateParameters(Position2d & pos);

	void setRotation(double newRot);

	void setSpeed(double x, double y);

	///Sets model linear speed (x,y) and angular speed (rotVel)
	void set(double xVel, double yVel, double rotVel);

	void goToPosition(Position2d * pos);

	void stop();

	void doTest();

	const std::string & getModelName();
private:


	gazebo::PositionIface * posIface;

	std::string modelName; //TODO: to jest nadmiarowe... ale uzywane do zapisu danych do debugowania

	static log4cxx::LoggerPtr logger;

	class MotionControl
	{
	public:
		static double calcSpeed(double currSpeed, double currPos, double dest);
		static Vector2d calcSpeed(const Vector2d & currSpeed, const Vector2d & currPos, const Vector2d & dest);
	};
};

#endif /* DRIVER_H_ */
