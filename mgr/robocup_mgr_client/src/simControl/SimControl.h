/*
 * SimControl2.h
 *
 *  Created on: 2009-03-09
 *      Author: kamil
 */
#ifndef SIMCONTROL_H_
#define SIMCONTROL_H_

#include <stack>
#include <gazebo.h>
#include <string.h>
#include <gazebo/GazeboError.hh>

#include "../util/position2d/Position2d.h"

#include "log4cxx/logger.h"

class SimControl {
public:
	static SimControl &  getInstance();
	~SimControl();

	void addRequest(gazebo::SimulationRequestData::Type type, const char * modelName);
	void processRequests();

	void requestPositions(std::map<std::string, Position2d *>  models);
	void update(std::map<std::string, Position2d *>  models);

	double getSimTime();

	gazebo::Client * getClient();

private:
	static log4cxx::LoggerPtr logger;
	std::stack<gazebo::SimulationRequestData *> requests;

	SimControl();
	SimControl(const SimControl & sc) {};

	///wskaznik na klienta odpowiadającego za połączenie z gazebo
	gazebo::Client* client;
	///instancja interfejsu symulacyjnego
	gazebo::SimulationIface* simIface;

	///czas symulacji, ustawiany w momencie uruchomienia metody update;
	///dzieki temu czas symulacji odpowiada momentowi, w ktorym odebrane byly pozycje robotów
	double simTime;
};

#endif /* SIMCONTROL2_H_ */
