/*
 * AppConfig.h
 *
 *  Created on: 2009-12-13
 *      Author: kamil
 */

#ifndef APPCONFIG_H_
#define APPCONFIG_H_

#include "rapidxml.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "log4cxx/logger.h"
#include "util/vector2d/Vector2d.h"


/**
 * This class holds general config data for whole application.
 *
 * This includes: information about robots, teams and so on
 *
 * Config fields are public for easy access.
 *
 * TODO: describe config file struct
 * TODO: make this a singletone?..
 */
class AppConfig {
public:
	///Singleton access method
	static AppConfig & instance();

	///Team 1 members - model names
	std::vector<std::string> team1;
	///Team 2 members - model names
	std::vector<std::string> team2;
	///Ball model name (it supposed to be ball, but who knows ?:) )
	std::string ball;

	///Robot radius
	double radius;

	///Field size
	Vector2d fieldSize;
private:
	/**
	 * Constructor is responsible for filling apropriate public fields in the config object.
	 *
	 * @param filename name of file containing config
	 */
	AppConfig(std::string filename);

	AppConfig(const AppConfig &);

	AppConfig & operator=(const AppConfig &);

	~AppConfig();

	///Just for logging purposes
	static log4cxx::LoggerPtr logger;
};

#endif /* APPCONFIG_H_ */
