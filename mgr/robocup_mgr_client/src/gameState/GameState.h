/*
 * GameState.h
 *
 *  Created on: 2009-03-09
 *      Author: kamil
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <map>
#include <gazebo.h>
#include "log4cxx/logger.h"
#include "../util/position2d/Position2d.h"

class GameState {

////////////////////////////////	interfejsy	/////////////////////////////////////////////
public:
	GameState(std::string configFile);
	~GameState();

	/**
	 * aktualizacja polozenia modeli
	 * pobieranie czasu symulacji
	 * obliczenie TAlg
	 **/
	bool update();


	void display();

	Position2d * getModelPos(std::string name);

	double getTalg();

	std::map<std::string , Position2d *> * getModels();

/////////////////////////////////////////////////////////////////////////////////////////////
private:
	//okres, co jaki jest uruchamiany update (czas zgodny z czasem symulacji)
	double Talg;
	double prevSimTime;
	std::map<std::string , Position2d *> models;

	static log4cxx::LoggerPtr logger;

	void loadConfig(std::string filename);
	void requestModelPositions();
};

#endif /* GAMESTATE_H_ */
