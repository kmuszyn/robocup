/*
 * Robot.cpp
 *
 *  Created on: 2009-05-04
 *      Author: kamil
 */

#include "Robot.h"
#include <iostream>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

log4cxx::LoggerPtr Robot::logger(log4cxx::Logger::getLogger("robot.Robot"));

Robot::Robot(std::string modelName, TeamName team, GameState * gameState) : driver(modelName) {
	this->modelName = modelName;
	this->team = team;
	this->gameStatePtr = gameState;
}

Robot::~Robot() {
	LOG4CXX_DEBUG(logger,"Destroying robot: "<<modelName);
	this->gameStatePtr = 0;
}

void Robot::doTest(){
//	Position2d * pose = gameStatePtr->getModelPos(modelName);
/*
	Vector2d dest(2.7,3.7);



	////// pomiar czasu
	boost::posix_time::ptime t1 = boost::posix_time::ptime(boost::posix_time::microsec_clock::local_time());
	///////////






	RRT rrt(this->modelName,this->gameStatePtr);
	Vector2d tmp = rrt.plan(dest);


	////// pomiar czasu
	boost::posix_time::ptime t2 = boost::posix_time::ptime(boost::posix_time::microsec_clock::local_time());
	boost::posix_time::time_duration tdur = t2-t1;
	double tAlg = static_cast<double> (tdur.total_microseconds()/1000000.0);

	std::cout<<"Time elapsed: "<<tAlg<<std::endl;

	///////////



	double angle = Vector2d(1,0).angleTo(tmp-pose->pos);



	std::cout<<"*********************\n";
	std::cout<<"Robot pos: "<<pose->pos<<std::endl;
	std::cout<<"Robot pos next: "<<tmp<<std::endl;



	std::cout<<"Angle: "<<angle<<std::endl;


	if( (pose->pos - dest).length() > 0.05){
		this->driver.setSpeed(10*cos(angle),10*sin(angle));
		this->driver.setRotation(0);
		std::cout<<"speed: "<<cos(angle)<<","<<sin(angle)<<std::endl;
	}
	else{
		std::cout<<"KONIEC\n";
		this->driver.stop();
		exit(0);
	}

*/


//	static double startTime = SimControl::getInstance().getSimTime();
//
//	if (SimControl::getInstance().getSimTime() < startTime + 5.0){
//
////		std::cout<<"Model: "<<modelName<<" yaw "<<pose->rot.val<<
////			" TALG: "<<gameStatePtr->getTalg()<<std::endl;
//		driver.updateParameters(pose, gameStatePtr->getTalg());
//
//		driver.doTest();
//	}
//	else{
//		driver.stop();
//		std::cout<<"KONIEC\n";
//		std::cout<<"Model: "<<modelName<<" pozycja: "<<pose->pos.x<<" "<<pose->pos.y<<std::endl;
//		std::cout<<"Sim time: "<<SimControl::getInstance().getSimTime()<<std::endl;
//
//		exit(0);
//
//	}
	driver.doTest();
}
