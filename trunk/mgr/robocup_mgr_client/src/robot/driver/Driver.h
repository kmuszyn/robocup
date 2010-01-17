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

	void goToPosition(Position2d * pos);

	void stop();

	void doTest();
private:


	gazebo::PositionIface * posIface;

	std::string modelName; //TODO: to jest nadmiarowe... ale uzywane do zapisu danych do debugowania

	static log4cxx::LoggerPtr logger;

	struct DriverData{
		double dX, dY, dRot;
		double lastUpdateTime;
		Position2d lastPos;
		double updatePeriod;
	} driverData;
};

#endif /* DRIVER_H_ */
