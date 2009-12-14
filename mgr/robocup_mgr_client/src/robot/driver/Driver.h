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
#include <gazebo.h>

#include "../../simControl/SimControl.h"
#include "../../util/position2d/Position2d.h"

class Driver {
public:
	Driver(std::string modelName);
	~Driver();

	///Metoda aktualizująca parametry używane przez sterownik - prędkości liniową i kątową
	void updateParameters(Position2d * pose, double Talg);

	void setRotation(double newRot);

	void setSpeed(double x, double y);

	void goToPosition(Position2d * pos);

	void stop();

	void doTest();
private:
	///parametry chwilowe robota, wyliczane na podstawie zmiany położenia i rotacji
	///prędkość liniowa (chwilowa)
	double v;
	///prędkość kątowa (chwilowa)
	double w;
	///aktualna pozycja robota (położenie + rotacja), ustawiana w momencie aktualizacji parametrów
	Position2d currPos;

	gazebo::PositionIface * posIface;

	std::string modelName; //TODO: to jest nadmiarowe...

	static log4cxx::LoggerPtr logger;
};

#endif /* DRIVER_H_ */
