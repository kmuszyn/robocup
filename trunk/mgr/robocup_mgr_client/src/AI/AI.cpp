/*
 * AI.cpp
 *
 *  Created on: 2010-01-10
 *      Author: kamil
 */

#include "AI.h"
#include "AI/task/GoTo.h"

AI::AI(std::string robotName, TeamName teamName) : robot(robotName, teamName){
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


void AI::act(){
	//if there is no task
	if (task == 0)
		generateTask();
	if (task->valid())
		task->execute();
	else{
		delete task;
		task = 0;
	}

#ifdef MGR_VIEWER
	writeViewerData();
#endif

	return;
}

/////////////////// private methods //////////////////////////////////////////

void AI::generateTask(){
	BOOST_ASSERT(task==0);
	Position2d pos(2,2,90);
	task = new GoTo(robot, pos);
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

	robot.writeViewerData();
}
#endif
