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
Driver::Driver(std::string modelName) {
	LOG4CXX_DEBUG(logger,"Creating driver for: "<<modelName);
	try{
		this->posIface = new gazebo::PositionIface();
		this->posIface->Open(SimControl::getInstance().getClient(),modelName+"::"+modelName);
	}
	catch(std::string ex){
		LOG4CXX_ERROR(logger, "Error creating Driver: "<<ex);
		exit(0);
	}

	this->v = 0;
	this->w = 0;
}

Driver::~Driver() {
	LOG4CXX_DEBUG(logger, "Destroying driver");
	this->posIface->Close();
}
///////////////////////////////////////////////////////////////////////////


void Driver::updateParameters(Position2d * newPos, double Talg){
//	Position2d newPos(pose->pos.x, pose->pos.y, Angle(pose->yaw));

	this->v = (( this->v) + ((newPos->pos - currPos.pos).length()/Talg)) / 2;
	this->w = ( 9*(this->w) + (((newPos->rot - currPos.rot).val)/Talg)) / 10;

	//aktualizacja dotychczasowej pozycji
	this->currPos = *newPos;
}

void Driver::setRotation(double newRot){

	double e = (this->currPos.rot - newRot).val;

	posIface->Lock(1);
	posIface->data->cmdEnableMotors = 1;
	posIface->data->cmdVelocity.yaw = 10 * (-e);
	posIface->Unlock();
}

void Driver::setSpeed(double x, double y){
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
	posIface->data->cmdVelocity.pos.x = 0;//sin(this->currPos.rot.val);
	posIface->data->cmdVelocity.pos.y = 10;//cos(this->currPos.rot.val);
	posIface->data->cmdVelocity.yaw = 0;//5.0;
	posIface->Unlock();

//	std::cout.precision(6);
//	std::cout<<"driver::test: "<<this->currPos.pos<<" "<<v<<" "<<w<<std::endl;

}
