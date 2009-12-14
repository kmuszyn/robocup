/*
 * GameState.cpp
 *
 *  Created on: 2009-03-09
 *      Author: kamil
 */

#include "GameState.h"
#include "../simControl/SimControl.h"
#include <gazebo.h>

//do parsera
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <boost/lexical_cast.hpp>


log4cxx::LoggerPtr GameState::logger(log4cxx::Logger::getLogger("gameState.GameState"));

GameState::GameState(std::string filename) {
	//wczytanie pliku z konfiguracją modeli
	this->loadConfig(filename);
	//wyslanie pierwszego zapytania o pozycję modeli do gazebo - żeby w przypadku update były już pobrane pozycje robotów
	this->requestModelPositions();
	//pobieranie czasu
	this->prevSimTime = SimControl::instance().getSimTime();
}

GameState::~GameState() {
	LOG4CXX_DEBUG(logger, "~GameState");
	models.clear();
}

void GameState::requestModelPositions(){
	SimControl::instance().requestAllPositions(models);
}

bool GameState::update(){
/*	if (SimControl::instance().update(models)){
		double currSimTime=SimControl::instance().getSimTime();

		this->Talg=currSimTime-prevSimTime;
		this->prevSimTime=currSimTime;

		return true;
	}
*/
	return false;
}


void GameState::display(){
	std::cout<<"Zawartość GameState:\n";
	std::map<std::string, Position2d *>::iterator ii = models.begin();
	std::cout.precision(3);
	for(;ii!=models.end(); ii++){
		std::cout<<"*** model: "<<ii->first<<std::endl;
		std::cout<<" pos: ("<<ii->second->pos.x<<",";
		std::cout<<ii->second->pos.y<<")\n";

		std::cout<<" rot: ("<<ii->second->rot.val<<")"<<std::endl;
	}
}

double GameState::getTalg(){
	return Talg;
}

void GameState::loadConfig(std::string filename){
	LOG4CXX_DEBUG(logger, "Wczytywanie pliku konfiguracyjnego: "<<filename);

	xmlDocPtr config;
	xmlNodePtr current;
	std::string team1Name;
	std::string team2Name;
	std::string ballName;
	int teamCount=0;


	config = xmlParseFile(filename.c_str());

	if (config == 0 ) {
		LOG4CXX_ERROR(logger,"Brak pliku: "<<filename);
		exit(0);
	}

	current = xmlDocGetRootElement(config);

	if (current == 0) {
		LOG4CXX_ERROR(logger, "Błąd w pliku: "<<filename<<" - pusty plik");
		xmlFreeDoc(config);
		exit(0);
	}

	if (xmlStrcmp(current->name, (const xmlChar *) "config")) {
		LOG4CXX_ERROR(logger,"Root node!= config w pliku XML "<<filename);
		xmlFreeDoc(config);
		return;
	}

	current = current->xmlChildrenNode;
	while (current != 0) {
//		LOG4CXX_DEBUG(logger,"curr node: "<<current->name);
		if(!xmlStrcmp(current->name,(const xmlChar *) "team1")){
			xmlChar * str;
			str = xmlNodeListGetString(config,current->xmlChildrenNode,1);
			team1Name = std::string((const char *) str);
			xmlFree(str);
		}

		if(!xmlStrcmp(current->name,(const xmlChar *) "team2")){
			xmlChar * str;
			str = xmlNodeListGetString(config,current->xmlChildrenNode,1);
			team2Name = std::string((const char *) str);
			xmlFree(str);
		}

		if(!xmlStrcmp(current->name,(const xmlChar *) "ball")){
			xmlChar * str;
			str = xmlNodeListGetString(config,current->xmlChildrenNode,1);
			ballName = std::string((const char *) str);
			xmlFree(str);
		}

		if(!xmlStrcmp(current->name,(const xmlChar *) "teamCount")){
			xmlChar * str;
			str = xmlNodeListGetString(config,current->xmlChildrenNode,1);
			teamCount = boost::lexical_cast<int>(str);
			xmlFree(str);
		}

		current = current->next;
	}

	xmlFreeDoc(config);

	//uzupełnianie nazw modeli
//	LOG4CXX_DEBUG(logger,"team1 "<<team1Name);
//	LOG4CXX_DEBUG(logger,"team2 "<<team2Name);
//	LOG4CXX_DEBUG(logger,"ball "<<ballName);
//	LOG4CXX_DEBUG(logger,"teamcount "<<teamCount);


	for(int i = 0; i < teamCount; i++){
		std::string modelName(team1Name + (char)(i+'0'));
		models[modelName] = new Position2d();
//		LOG4CXX_DEBUG(logger, "petla "<<(team1Name + (char)(i+'0')).c_str());
	}

	for(int i = 0; i < teamCount; i++){
		std::string modelName(team2Name + (char)(i+'0'));
		models[modelName] = new Position2d();
//		LOG4CXX_DEBUG(logger, "petla "<<(team2Name + (char)(i+'0')).c_str());
	}

	models[ballName.c_str()] = new Position2d();


}

std::map<std::string , Position2d *> * GameState::getModels(){
	return & models;
}


Position2d * GameState::getModelPos(std::string name){
	return this->models[name];
}
