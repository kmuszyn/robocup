/*
 * AppConfig.cpp
 *
 *  Created on: 2009-12-13
 *      Author: kamil
 */

#include "AppConfig.h"

log4cxx::LoggerPtr AppConfig::logger(log4cxx::Logger::getLogger("config.AppConfig"));

AppConfig::AppConfig(std::string filename) {
	std::ifstream configFile;
	std::string line;
	std::string fileContent;

	configFile.open(filename.c_str());

	if (!configFile) {
		LOG4CXX_ERROR(logger, "Config file not found "+filename);
		throw new std::string("Config file" + filename + "not found!");
	}

	while(std::getline(configFile, line))
		fileContent.append(line);

	std::vector<char> copy(fileContent.begin(), fileContent.end());
	copy.push_back('\0');

	rapidxml::xml_document<> doc;
	doc.parse<0>(&copy[0]);

	//getting team members names
	rapidxml::xml_node<> * curr_node = doc.first_node("config")->first_node("team1")->first_node("player");
	team1.push_back(curr_node->value());
	while(curr_node->next_sibling("player") != 0){
		curr_node = curr_node->next_sibling("player");
		team1.push_back(curr_node->value());
	}
	curr_node = doc.first_node("config")->first_node("team2")->first_node("player");
	team2.push_back(curr_node->value());
	while(curr_node->next_sibling("player") != 0) {
		curr_node = curr_node->next_sibling("player");
		team2.push_back(curr_node->value());
	}

	//ball model name
	curr_node = doc.first_node("config")->first_node("ball");
	ball = curr_node->value();

}

AppConfig::~AppConfig() {

}

AppConfig & AppConfig::instance(){
	static AppConfig appConfig("../config/models.xml");
	return appConfig;
}
