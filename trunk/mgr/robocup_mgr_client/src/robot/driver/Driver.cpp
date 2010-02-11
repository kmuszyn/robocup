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
}

Driver::~Driver() {
	LOG4CXX_DEBUG(logger, "Destroying driver");
	this->posIface->Close();
}
///////////////////////////////////////////////////////////////////////////

void Driver::goToPosition(Position2d * pos){

	//calculating (x,y) speed

	LOG4CXX_DEBUG(logger, "****** Driver, goto position: "<<pos->pos);
	Position2d * curr = (VideoServer::instance().data())[modelName];
	LOG4CXX_DEBUG(logger, "****** Driver, current position: "<<curr->pos);
	Vector2d diff = pos->pos - curr->pos;

	LOG4CXX_DEBUG(logger, "Distance to target: "<<diff.length());
	LOG4CXX_DEBUG(logger, "Distance vec: "<<diff);

	double scale = 2.0;

	//if (diff.length() < 0.25) scale = 0.5;

	diff = diff * (scale / diff.length());

	LOG4CXX_DEBUG(logger, "Distance vec after scalling: "<<diff);

	LOG4CXX_DEBUG(logger, "Diff1: "<<diff);

	diff = diff.rotate(-(curr->rot.val));

	LOG4CXX_DEBUG(logger, "diff2: "<<diff);

	LOG4CXX_DEBUG(logger, "Desired speed: "<<diff);

	//calculating rotation speed

	Vector2d vcurr(cos(curr->rot.val),sin(curr->rot.val));
	Vector2d vdest(cos(pos->rot.val),sin(pos->rot.val));

	double angle2rot = vcurr.angleTo(vdest);
	//std::cout<<"Angle2: "<<angle2rot<<std::endl;

	double vRot = (angle2rot)*3;

//	std::cout<<"Predkosc: "<<diff<<std::endl;
//	std::cout<<"Rotacja: "<<curr->rot.val<<std::endl;
//	std::cout<<"Poz: " << curr->pos<<std::endl;

	set(diff.x, diff.y, vRot);

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

void Driver::set(double x, double y, double rot){
	posIface->Lock(1);
	posIface->data->cmdEnableMotors = 1.0;
	posIface->data->cmdVelocity.pos.x = x;
	posIface->data->cmdVelocity.pos.y = y;
	posIface->data->cmdVelocity.yaw = rot;
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

const std::string & Driver::getModelName(){
	return this->modelName;
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
