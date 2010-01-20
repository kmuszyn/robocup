/*
 * RRT.cpp
 *
 *  Created on: 2009-05-10
 *      Author: kamil
 */

#include "RRT.h"


RRT::RRT(std::string modelName) {
	this->modelName = modelName;
	rrttree = 0;
}

RRT::~RRT() {
	delete rrttree;
}

Vector2d RRT::plan(Vector2d goal){
	const double THRESHOLD = 0.05;

	if (rrttree!=0) delete rrttree;
	Position2d * robotPos = (VideoServer::instance().data())[modelName];
	this->rrttree = new RRTTree(robotPos->pos);
	RRTTreeNode * nearest;
	do{
		Vector2d target = chooseTarget(goal);
		nearest = this->rrttree->findNearest(target);
		if ((nearest->position - goal).length() < THRESHOLD)
			break; //warunek końca spełniony
		Vector2d extended = extend(nearest->position, target);
		if (extended.x > -1) //co oznacza, ze stworzony punkt nie koliduje z niczym
			this->rrttree->addNode(extended, nearest);
//		this->rrttree->display();
	 }while(true);

	//tutaj: gotowe drzewo

//	std::cout<<"Sciezka: \n";

	RRTTreeNode * tmp = nearest;
	RRTTreeNode * root = this->rrttree->getRoot();

//	std::cout<<"root: "<<root->position<<std::endl;
	while(tmp->parent!=root){
//		std::cout<<"Tmp: "<<tmp->position<<" parent: "<<tmp->parent->position<<std::endl;
		tmp = tmp->parent;
	}
//	this->rrttree->print2tex(robotPos->pos, goal, this->gameStatePtr);
//	exit(0);
	return tmp->position;

}

Vector2d RRT::extend(Vector2d begin, Vector2d goal){
	double distance = AppConfig::instance().radius;

	double length = (goal-begin).length();
	double cosAlfa = (goal.x - begin.x) / length;
	double sinAlfa = (goal.y - begin.y) / length;

	Vector2d result((distance * cosAlfa) + begin.x, (distance * sinAlfa) + begin.y);

	if (this->checkCollisions(result) == false) //brak kolizji
		return result;
	else
		return Vector2d(-1,-1);
}

bool RRT::checkCollisions(const Vector2d & point){
	std::map<std::string, Position2d*>::iterator ii = VideoServer::instance().data().begin();
	for(;ii!=VideoServer::instance().data().end(); ii++){
		if( ii->first==this->modelName) continue;
		if((point - ii->second->pos).length() < 2 * AppConfig::instance().radius) return true;
	}

	return false;
}

Vector2d RRT::chooseTarget(Vector2d goal){
	float p = getRand();
	if ( p < this->GOAL_PROB){
		return goal;
	} else{
		return randomTarget();
	}
}

Vector2d RRT::randomTarget(){

	//TODO: wymiary boiska pobierac z configa?
	//odejmowanie 0.08 zeby robot nie wjechal na bande
	AppConfig & conf = AppConfig::instance();
	Vector2d res((conf.fieldSize.x - conf.radius) * getRand() + conf.radius,
			(conf.fieldSize.y - conf.radius) * getRand() + conf.radius);
	return res;
}

float RRT::getRand(){
	return ((float) rand() / RAND_MAX);
}

#ifdef MGR_VIEWER
void RRT::writeViewerData(std::ofstream & s){
	rrttree->writeViewerData(s);
}

int RRT::countNodes(){
	return rrttree->countNodes();
}
#endif
