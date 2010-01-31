/*
 * Robot.cpp
 *
 *  Created on: 2009-05-04
 *      Author: kamil
 */

#include "Robot.h"


log4cxx::LoggerPtr Robot::logger(log4cxx::Logger::getLogger("robot.Robot"));

Robot::Robot(std::string name, TeamName team) : driver(name), ai(name, team){
	this->name = name;
	this->team = team;
}

Robot::~Robot() {
	LOG4CXX_DEBUG(logger,"Destroying robot: "<<name);
}


void Robot::makeMove(){
	Task *t = ai.assignTask();
	t->execute(driver);
}


/*
void Robot::goTo(Position2d & pos){
	RRT rrt(this->modelName);
	Vector2d tmp = rrt.plan(pos.pos);
	Position2d tmpPos;
	tmpPos.pos = tmp;
	driver.goToPosition(&tmpPos);

#ifdef MGR_VIEWER
	writeViewerData(rrt);
#endif
}
*/

#ifdef MGR_VIEWER
void Robot::writeViewerData(RRT & rrt){
	std::ofstream file;
	file.open((name+".txt").c_str(),std::ios::app);
	Position2d * pos = VideoServer::instance().data()[name];
	file<<":robot\n";
	file<<pos->pos.x<<" "<<pos->pos.y<<" "<<pos->rot.degreeValue()<<std::endl;

	//write rrt part
	file<<":rrt "<<rrt.countNodes()<<std::endl;
	rrt.writeViewerData(file);

	file.close();
}
#endif
