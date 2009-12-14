/*
 * SimControl2.cpp
 *
 *  Created on: 2009-03-09
 *      Author: kamil
 */

#include "SimControl.h"

log4cxx::LoggerPtr SimControl::logger(log4cxx::Logger::getLogger("simControl.SimControl"));

SimControl & SimControl::instance(){
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
	} catch (std::string e) {
		LOG4CXX_ERROR(logger,"Gazebo error: Unable to connect to the sim interface\n" << e );
		exit(0);
	}


	LOG4CXX_DEBUG(logger, "SimControl construct, sending request (model positions)");

	//this requests are necessary for SimControl::update() to work properly
	VideoData videoData = VideoServer::instance().data();

	VideoData::iterator ii = videoData.begin();
	for (; ii != videoData.end(); ii++) {
		this->sendRequest(gazebo::SimulationRequestData::GET_POSE3D,
		ii->first.c_str());
	}

}

SimControl::~SimControl() {
	this->simIface->Destroy();
	delete this->simIface;

	this->client->Disconnect();
	delete this->client;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void SimControl::sendRequest(gazebo::SimulationRequestData::Type type, const char * modelName){
//	gazebo::SimulationRequestData * req = new gazebo::SimulationRequestData();
//	req->type = type;
//	memcpy(req->modelName, modelName,512);
//	this->requests.push(req);


	gazebo::SimulationRequestData * req = & simIface->data->requests[simIface->data->requestCount++];
	req->type = type;
	memcpy(req->modelName,modelName, 512);
//	req->modelPose = queuedReq->modelPose;


}

//void SimControl::processRequests(){
//
////	simIface->Lock(1);
//	while(!this->requests.empty()){
//		LOG4CXX_DEBUG(logger, "Ilosc requestow: " << simIface->data->requestCount);
//		gazebo::SimulationRequestData * queuedReq = this->requests.top();
//
//		gazebo::SimulationRequestData * req = & simIface->data->requests[simIface->data->requestCount++];
//		req->type = queuedReq->type;
//		memcpy(req->modelName,queuedReq->modelName, 512);
//		req->modelPose = queuedReq->modelPose;
//		this->requests.pop();
//		delete queuedReq;
//	}
////	simIface->Unlock();
//}

/////////////////////////////////////////////////////////////////////////////////////////////


void SimControl::requestAllPositions(std::map<std::string , Position2d *> models){
	simIface->Lock(1);
	//zadanie zapytania o pozycje wszystkich modeli
	std::map<std::string, Position2d *>::iterator ii = models.begin();
	for(;ii!=models.end(); ii++){
		this->sendRequest(gazebo::SimulationRequestData::GET_POSE3D, ii->first.c_str());
	}
	simIface->Unlock();
}

void SimControl::update(VideoData & videoData) {

	while(true){
		lock();
		int responseCount = simIface->data->responseCount;
		if (responseCount > 0) {
			LOG4CXX_DEBUG(logger,"RespCount "<<responseCount)
			//server response parsing
			for (; simIface->data->responseCount > 0; simIface->data->responseCount--) {
				gazebo::SimulationRequestData
						* response =
								&simIface->data->responses[simIface->data->responseCount - 1];
				LOG4CXX_DEBUG(logger, "Model name from response: "<<response->modelName);
				std::string modelName(response->modelName);
				Position2d modelPos(response->modelPose.pos.x,
						response->modelPose.pos.y, response->modelPose.yaw);
				*(videoData[modelName]) = modelPos;
			}

			//send further requests about robot positions
			VideoData::iterator ii = videoData.begin();
			for (; ii != videoData.end(); ii++) {
				this->sendRequest(gazebo::SimulationRequestData::GET_POSE3D,
						ii->first.c_str());
			}

			//simulation time update TODO: remove this?
			this->simTime = simIface->data->simTime;

			unlock();
			return;
		}
		unlock();
	}

}
/*

bool SimControl::update(std::map<std::string , Position2d *> models){
	//zakładam, że oczekujemy na jakieś odpowiedzi z serwera
	//co oznacza, ze wczesniej wywołano metodę request positions (co dzieje się np. w konstruktorze


	//WAZNE: wszystkie akcje zwiazane z UPDATE robione sa w jednym locku!

//	while(true){
//		simIface->Lock(1);
//		int responseCount = simIface->data->responseCount;
//		if (responseCount > 0){
//			LOG4CXX_DEBUG(logger,"RespCount "<<responseCount)
//			//przetworzenie wiadomości
//			for( ;simIface->data->responseCount>0;  simIface->data->responseCount--){
//				gazebo::SimulationRequestData * response = &simIface->data->responses[ simIface->data->responseCount-1];
//				LOG4CXX_DEBUG(logger, "Nazwa modelu z response: "<<response->modelName);
//				std::string modelName(response->modelName);
//				Position2d modelPos(response->modelPose.pos.x, response->modelPose.pos.y, response->modelPose.yaw);
//				*(models[modelName]) = modelPos;
//			}
//
//			//zadanie zapytania o pozycje wszystkich modeli
//			std::map<std::string, Position2d *>::iterator ii = models.begin();
//			for (; ii != models.end(); ii++) {
//				this->addRequest(gazebo::SimulationRequestData::GET_POSE3D,
//						ii->first.c_str());
//			}
//
//			//przetworzenie requestow
//			this->processRequests();
//
//			//uaktualnienie czasu symulacji
//			this->simTime=simIface->data->simTime;
//
//			break;
//		}
//		simIface->Unlock();
//	}



		lock();
		int responseCount = simIface->data->responseCount;
		if (responseCount > 0) {
			LOG4CXX_DEBUG(logger,"RespCount "<<responseCount)
			//przetworzenie odpowiedzi z serwera
			for (; simIface->data->responseCount > 0; simIface->data->responseCount--) {
				gazebo::SimulationRequestData * response =
						&simIface->data->responses[simIface->data->responseCount -1];
				LOG4CXX_DEBUG(logger, "Nazwa modelu z response: "<<response->modelName);
				std::string modelName(response->modelName);
				Position2d modelPos(response->modelPose.pos.x,
						response->modelPose.pos.y, response->modelPose.yaw);
				*(models[modelName]) = modelPos;
			}

			//zadanie zapytania o pozycje wszystkich modeli
			std::map<std::string, Position2d *>::iterator ii = models.begin();
			for (; ii != models.end(); ii++) {
				this->sendRequest(gazebo::SimulationRequestData::GET_POSE3D,
						ii->first.c_str());
			}

			//uaktualnienie czasu symulacji
			this->simTime = simIface->data->simTime;

			unlock();
			return true;
		}
		unlock();
		return false;
}*/

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

void SimControl::lock(){
	simIface->Lock(1);
}
void SimControl::unlock(){
	simIface->Unlock();
}
