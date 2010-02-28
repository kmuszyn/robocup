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

#include "util/types.h"

#include "videoServer/VideoServer.h"

#include "log4cxx/logger.h"

class SimControl {
public:
	///Returns the instance of SimControl class
	static SimControl &  instance();

	///Performs update of VideoData structure
	void update(VideoData & data);



	void sendRequest(gazebo::SimulationRequestData::Type type, const char * modelName);

	void requestAllPositions(std::map<std::string, Position2d *>  models);
	//bool update(std::map<std::string, Position2d *>  models);

	double getSimTime();

	gazebo::Client * getClient();

///////////////////////////////////////////////////////////////////////////////////////////
private:
	//hidden, for singleton implementation
	SimControl();
	SimControl(const SimControl & );
	SimControl & operator=(const SimControl &);
	~SimControl();

	bool lock();
	void unlock();
///////////////////////////////////////////////////////////////////////////////////////////
private:
	std::stack<gazebo::SimulationRequestData *> requests;
	///wskaznik na klienta odpowiadającego za połączenie z gazebo
	gazebo::Client* client;
	///instancja interfejsu symulacyjnego
	gazebo::SimulationIface* simIface;

	static log4cxx::LoggerPtr logger;
	///czas symulacji, ustawiany w momencie uruchomienia metody update;
	///dzieki temu czas symulacji odpowiada momentowi, w ktorym odebrane byly pozycje robotów
	double simTime;
};

#endif /* SIMCONTROL2_H_ */
