/*
 * Driver.cpp
 *
 *  Created on: 2009-05-04
 *      Author: kamil
 */

#include "Driver.h"
#include "robot/dynWindow/DynWindow.h"
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

	/*

	 curPos

	 calc of linear speed

	 Vector2d xy = DynWindow::calculate(robotName, pos->pos, currentSpeed)

	 caculation of rot speed


	 */

	//calculating (x,y) speed
	Position2d * curr = (VideoServer::instance().data())[modelName];
	Vector2d diff = pos->pos - curr->pos;

	Vector2d currSpeed;
	currSpeed.x = posIface->data->velocity.pos.x;
	currSpeed.y = posIface->data->velocity.pos.y;
	//std::cout<<"Curr speed: "<<currSpeed<<std::endl;
	//diff = DynWindow::calcSpeed(modelName, pos->pos, currSpeed);

//	diff.x = MotionControl::calcSpeed(currSpeed.x, curr->pos.x,pos->pos.x);
//	diff.y = MotionControl::calcSpeed(currSpeed.y, curr->pos.y,pos->pos.y);
//
//	std::cout<<"**** Test 1\n";
//	Vector2d result2 = MotionControl::calcSpeed(Vector2d(2,0), Vector2d(0,0), Vector2d(1,0));
//	std::cout<<"res: "<<result2<<std::endl;
//
//	std::cout<<"**** Test 2\n";
//	result2 = MotionControl::calcSpeed(Vector2d(0,2), Vector2d(0,0), Vector2d(1,0));
//	std::cout<<"res: "<<result2<<std::endl;

	//double scale = 2.0;
	//diff = diff * (scale / diff.length());

	diff = MotionControl::calcSpeed(currSpeed, curr->pos, pos->pos);
//	std::cout<<"Current robot rotation: "<<curr->rot.val<<std::endl;
	diff = diff.rotate(-(curr->rot.val));

//	std::cout<<"result after rotate: "<<diff<<std::endl;

	//calculating rotation speed

	Vector2d vcurr(cos(curr->rot.val),sin(curr->rot.val));
	Vector2d vdest(cos(pos->rot.val),sin(pos->rot.val));

	double angle2rot = vcurr.angleTo(vdest);
	//std::cout<<"Angle2: "<<angle2rot<<std::endl;

	double vRot = (angle2rot)*3;

	//std::cout<<"Calculated order: "<<diff<<std::endl;
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

Vector2d
Driver::MotionControl::calcSpeed(const Vector2d & currSpeed,
								 const Vector2d & currPos,
								 const Vector2d & dest)
{
	double VMAX = 2.0;
	double a = 8.3;
	double THRESHOLD = 0.01;
	Vector2d result;
	//disassembling currSpeed to 2 parts: pararell to vector to dest and perpendicular
	Vector2d destVec = dest - currPos;

//	std::cout<<"***************\nCurr pos: "<<currPos<<" dest:"<<dest<<std::endl;
//	std::cout<<"dest vec: "<<destVec<<std::endl;

	double angleToDest = destVec.angleTo(currSpeed);
	double parallel = currSpeed.length() * cos(angleToDest);
	double perpendicular = currSpeed.length() * sin(angleToDest);

//	std::cout<<"Parallel: "<<parallel<<" perpendicular: "<<perpendicular<<std::endl;

	//perpendicular part must be close to 0
	if (fabs(perpendicular)>THRESHOLD )
		perpendicular = -perpendicular;

	if (parallel < 0 && fabs(parallel) > THRESHOLD) //breaking if this part is in opposite dir
		parallel = -parallel;
	else
	{
		parallel = sqrt(2 * (dest-currPos).length() * a);
		if (parallel > VMAX) parallel = VMAX;
	}

//	std::cout<<"New values:\n";
//	std::cout<<"Parallel: "<<parallel<<" perpendicular: "<<perpendicular<<std::endl;


	result.x = parallel;
	result.y = perpendicular;
//	std::cout<<"Result: "<<result<<std::endl;


	//creating new vec by projection of result vec to OX
	double angle2OX = Vector2d(1,0).angleTo(destVec);
//	std::cout<<"angle2ox "<<angle2OX<<std::endl;
//	result.x = result.length() * cos(angle2OX);
//	result.y = result.length() * sin(angle2OX);
	result = result.rotate(angle2OX);

//	std::cout<<"Result after rotating OX: "<<result<<std::endl;

	return result;
}

double Driver::MotionControl::calcSpeed(double currSpeed, double currPos, double dest)
{
	//based on www.cs.cmu.edu/~mmv/papers/05nrl-jim.pdf, page 7

	double VMAX = 2.0;
	double a = 8.3;
	double dist = fabs(dest - currPos);
	double sgn = currSpeed > 0 ? 1 : -1;

	//desired speed direciton:
	double dir = dest - currPos;

	//1.
	if ( (currSpeed * dir) < 0)	//both have different signs, BREAKING
		return -currSpeed;

	//2.
	if (fabs(currSpeed) >= sqrt(2 * dist * a)) //BREAK
		return -currSpeed;

	//3.
	if (fabs(currSpeed) > VMAX + 0.01) //reduce to vmax
		return sgn * VMAX;

	//4. simplified for now
	double result = sqrt(2 * (dist) * a);
	if (result > VMAX) result = VMAX;
	return sgn * result;
}
