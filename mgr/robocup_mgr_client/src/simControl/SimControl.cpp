/*
 * SimControl2.cpp
 *
 *  Created on: 2009-03-09
 *      Author: kamil
 */

#include "SimControl.h"

log4cxx::LoggerPtr SimControl::logger(log4cxx::Logger::getLogger("simControl.SimControl"));

SimControl & SimControl::getInstance(){
	static SimControl sc;
	return sc;
}

SimControl::SimControl() {
	this->client = new gazebo::Client();
	this->simIface = new gazebo::SimulationIface();
	int serverId = 0;
	std::string id("default");

	try {
		/// Connect to the libgazebo server
		this->client->ConnectWait(serverId, GZ_CLIENT_ID_USER_FIRST);
		/// Open the Simulation Interface
		this->simIface->Open(client, id);
	} catch (gazebo::GazeboError e) {
		LOG4CXX_ERROR(logger,"Gazebo error: Unable to connect to the sim interface\n" << e );
		exit(0);
	}
}

SimControl::~SimControl() {
	this->simIface->Destroy();
	delete this->simIface;

	this->client->Disconnect();
	delete this->client;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void SimControl::addRequest(gazebo::SimulationRequestData::Type type, const char * modelName){
	gazebo::SimulationRequestData * req = new gazebo::SimulationRequestData();
	req->type = type;
	memcpy(req->modelName, modelName,512);
	this->requests.push(req);
}

void SimControl::processRequests(){

//	simIface->Lock(1);
	while(!this->requests.empty()){
		LOG4CXX_DEBUG(logger, "Ilosc requestow: " << simIface->data->requestCount);
		gazebo::SimulationRequestData * queuedReq = this->requests.top();

		gazebo::SimulationRequestData * req = & simIface->data->requests[simIface->data->requestCount++];
		req->type = queuedReq->type;
		memcpy(req->modelName,queuedReq->modelName, 512);
		req->modelPose = queuedReq->modelPose;
		this->requests.pop();
		delete queuedReq;
	}
//	simIface->Unlock();
}

/////////////////////////////////////////////////////////////////////////////////////////////


void SimControl::requestPositions(std::map<std::string , Position2d *> models){
	LOG4CXX_DEBUG(logger, "Request positions: start");

	//zadanie zapytania o pozycje wszystkich modeli
	std::map<std::string, Position2d *>::iterator ii = models.begin();
	for(;ii!=models.end(); ii++){
		this->addRequest(gazebo::SimulationRequestData::GET_POSE3D, ii->first.c_str());
	}
	//przetworzenie zapytan
	simIface->Lock(1);
	this->processRequests();
	simIface->Unlock();
	LOG4CXX_DEBUG(logger, "Koniec");
}


void SimControl::update(std::map<std::string , Position2d *> models){
	//zakładam, że oczekujemy na jakieś odpowiedzi z serwera
	//co oznacza, ze wczesniej wywołano metodę request positions (co dzieje się np. w konstruktorze


	//WAZNE: wszystkie akcje zwiazane z UPDATE robione sa w jednym locku!

	while(true){
		simIface->Lock(1);
		int responseCount = simIface->data->responseCount;
		if (responseCount > 0){
			LOG4CXX_DEBUG(logger,"RespCount "<<responseCount)
			//przetworzenie wiadomości
			for( ;simIface->data->responseCount>0;  simIface->data->responseCount--){
				gazebo::SimulationRequestData * response = &simIface->data->responses[ simIface->data->responseCount-1];
				LOG4CXX_DEBUG(logger, "Nazwa modelu z response: "<<response->modelName);
				std::string modelName(response->modelName);
				Position2d modelPos(response->modelPose.pos.x, response->modelPose.pos.y, response->modelPose.yaw);
				*(models[modelName]) = modelPos;
			}

			//zadanie zapytania o pozycje wszystkich modeli
			std::map<std::string, Position2d *>::iterator ii = models.begin();
			for (; ii != models.end(); ii++) {
				this->addRequest(gazebo::SimulationRequestData::GET_POSE3D,
						ii->first.c_str());
			}

			//przetworzenie requestow
			this->processRequests();

			//uaktualnienie czasu symulacji
			this->simTime=simIface->data->simTime;

			break;
		}
		simIface->Unlock();
	}
}

double SimControl::getSimTime()
{
//	double result;
//	simIface->Lock(1);
//	result=simIface->data->simTime;
//	simIface->Unlock();
//	return result;

	return this->simTime;
}

gazebo::Client * SimControl::getClient(){
	return this->client;
}
