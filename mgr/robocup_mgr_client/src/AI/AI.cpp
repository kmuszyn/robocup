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

	bool valid = task->valid();
	bool finished = task->finished();

	if (!valid || finished){

		std::cout<<"Task ENDED, valid: "<<valid<<" finished: "<<finished<<"\n";
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
	float x = 0.8 + (float(rand()) / RAND_MAX) * (5.4 - 1.6);
	float y = 0.8 + (float(rand()) / RAND_MAX) * (7.4 - 1.6);
	float rot = - M_PI + (float(rand()) / RAND_MAX) * 2 * M_PI;

//	Position2d pos(1,4.5,rot);
//	Position2d pos(4, 0.5, rot);
	Position2d pos(x,y,rot);

	//Position2d * ballPos = VideoServer::instance().data()[AppConfig::instance().ball];
	//std::cout<<"Ball pos"<<*ballPos<<std::endl;

	task = new GoTo(pos, robotName);

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
