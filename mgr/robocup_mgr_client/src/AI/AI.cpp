/*
 * AI.cpp
 *
 *  Created on: 2010-01-10
 *      Author: kamil
 */

#include "AI.h"
#include "AI/task/GoTo.h"

AI::AI(std::string robotName, TeamName teamName) : robotName(robotName), teamName(teamName){
	task = 0;

#ifdef MGR_VIEWER
	//clear file used to write debug data
	debugFile = robotName + ".txt";
	std::ofstream file;
	file.open(debugFile.c_str(),std::ios::out);
	file.close();
#endif
}

AI::~AI() {
	delete task;
	task = 0;
}


Task * AI::assignTask(){
	//if there is no task
	if (task == 0){
		std::cout<<"Task 0\n";
		generateTask();
	}

	if (!(task->valid()) || task->finished()){
		std::cout<<"Task ||\n";
		delete task;
		task = 0;
		generateTask();
	}

#ifdef MGR_VIEWER
	writeViewerData();
#endif

	return task;
}

/////////////////// private methods //////////////////////////////////////////

void AI::generateTask(){
	//BOOST_ASSERT(task==0);
	float x = (float(rand()) / RAND_MAX) * 5.4;
	float y = (float(rand()) / RAND_MAX) * 7.4;
	Position2d pos(0.7,1.5,90);
	//Position2d pos(x,y,90);

	//Position2d * ballPos = VideoServer::instance().data()[AppConfig::instance().ball];
	//std::cout<<"Ball pos"<<*ballPos<<std::endl;

	task = new GoTo(pos);

	std::cout<<"Generated task: goTo:"<<pos<<std::endl;
}


#ifdef MGR_VIEWER
void AI::writeViewerData(){
	std::ofstream file;
	file.open(debugFile.c_str(),std::ios::app);

	file<<":step "<<VideoServer::instance().updateCounter<<std::endl;
	file<<":ai\n";
	file<<task->getName()<<std::endl;
	file<<task->getInfo()<<std::endl;
	file.close();

	//robot.writeViewerData();
}
#endif
