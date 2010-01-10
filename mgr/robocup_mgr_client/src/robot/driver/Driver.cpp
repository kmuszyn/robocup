/*
 * Driver.cpp
 *
 *  Created on: 2009-05-04
 *      Author: kamil
 */

#include "Driver.h"
#include <math.h>

log4cxx::LoggerPtr Driver::logger(log4cxx::Logger::getLogger("robot.driver.Driver"));


/////////////////////////////////////////////////////////////////////////
Driver::Driver(std::string modelName) : modelName (modelName){
	LOG4CXX_DEBUG(logger,"Creating driver for: "<<modelName);
	try{
		this->posIface = new gazebo::PositionIface();
		this->posIface->Open(SimControl::instance().getClient(),modelName+"::position_iface");
	}
	catch(std::string ex){
		LOG4CXX_ERROR(logger, "Error creating Driver: "<<ex);
		exit(0);
	}

	driverData.lastUpdateTime = 0;
	driverData.updatePeriod = 10 * 0.001;

}

Driver::~Driver() {
	LOG4CXX_DEBUG(logger, "Destroying driver");
	this->posIface->Close();
}
///////////////////////////////////////////////////////////////////////////

void Driver::goToPosition(Position2d * pos){

	LOG4CXX_DEBUG(logger, "****** Driver, goto position: "<<pos->pos);
	Position2d * curr = (VideoServer::instance().data())[modelName];
	LOG4CXX_DEBUG(logger, "****** Driver, current position: "<<curr->pos);
	Vector2d diff = pos->pos - curr->pos;


	//updateParameters(*curr);
	LOG4CXX_DEBUG(logger, "Distance to target: "<<diff.length());
	LOG4CXX_DEBUG(logger, "Distance vec: "<<diff);

	double scale = 2.0;

	diff = diff * (scale / diff.length());

	LOG4CXX_DEBUG(logger, "Distance vec after scalling: "<<diff);


	LOG4CXX_DEBUG(logger, "Diff1: "<<diff);

	diff = diff.rotate(-(curr->rot.val));

	LOG4CXX_DEBUG(logger, "diff2: "<<diff);

	LOG4CXX_DEBUG(logger, "Desired speed: "<<diff);

	setSpeed(diff.x, diff.y);
	//setRotation(1);

	LOG4CXX_DEBUG(logger, "Actual speeds: "<<driverData.dX<<" "<<driverData.dY<<" "<<driverData.dRot);
	//TODO: uwzglednic orientacje robota :)
}

void Driver::updateParameters(Position2d & newPos){

	double simTime = SimControl::instance().getSimTime();

	if (simTime - driverData.lastUpdateTime > driverData.updatePeriod){

		LOG4CXX_DEBUG(logger, "NEW PARAMS FOR DRIVER!!!!!!!!!!!!!!!!!!111");

		double dT = simTime - driverData.lastUpdateTime;

		driverData.dX = (newPos.pos.x - driverData.lastPos.pos.x) / dT;
		driverData.dY = (newPos.pos.y - driverData.lastPos.pos.y) / dT;
		//TODO: proper rot update
		driverData.dRot = (newPos.rot.val - driverData.lastPos.rot.val) / dT;
		//assign new values
		driverData.lastPos = newPos;
		driverData.lastUpdateTime = simTime;
	}

}

void Driver::setRotation(double newRot){

	//double e = (this->currPos.rot - newRot).val;

	posIface->Lock(1);
	posIface->data->cmdEnableMotors = 1;
	posIface->data->cmdVelocity.yaw = newRot;
	posIface->Unlock();
}

void Driver::setSpeed(double x, double y){
	//SETTING speed
	posIface->Lock(1);
	posIface->data->cmdEnableMotors = 1.0;
	posIface->data->cmdVelocity.pos.x = x;
	posIface->data->cmdVelocity.pos.y = y;
	posIface->Unlock();
}

void Driver::stop(){
	posIface->Lock(1);
	posIface->data->cmdEnableMotors = 0;
	posIface->data->cmdVelocity.pos.x = 0.0;
	posIface->data->cmdVelocity.pos.y = 0.0;
	posIface->data->cmdVelocity.yaw = 0;
	posIface->Unlock();
}

///////////////////////////////// metody testowe ///////////////////////////
void Driver::doTest(){

	posIface->Lock(1);
	posIface->data->cmdEnableMotors = 1.0;
	posIface->data->cmdVelocity.pos.x = 1.0;//*sin(this->currPos.rot.val);
	posIface->data->cmdVelocity.pos.y = 0.0;//*cos(this->currPos.rot.val);
	posIface->data->cmdVelocity.yaw = 0.0;//5.0;
	posIface->Unlock();

//	std::cout.precision(6);
//	std::cout<<"driver::test: "<<this->currPos.pos<<" "<<v<<" "<<w<<std::endl;

}
