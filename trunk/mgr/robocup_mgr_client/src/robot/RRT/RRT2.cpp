/*
 * RRT2.cpp
 *
 *  Created on: 2010-02-11
 *      Author: kamil
 */

#include "RRT2.h"
#include "videoServer/VideoServer.h"

RRT2::RRT2(const string & modelName) : modelName(modelName){

}

RRT2::~RRT2() {
	// TODO Auto-generated destructor stub
}

void RRT2::plan(const Vector2d & dest, Vector2d & point){
	Position2d * robotPos = (VideoServer::instance().data())[modelName];
	//if robot already at dest point
	if ((robotPos->pos - dest).length() < THRESHOLD){
		point = dest;
		return;
	}

	//creating a tree
	Node * root = new Node(robotPos->pos.x, robotPos->pos.y);

	//while dest point not reached
	while(true){
		Vector2d target = getTarget(dest);
		Node * nearest = root->findNearest(target);
		nearest->extend(target);
	}

	//dopoki nie koniec
	//wybor punktu docelowego
	//znalezienie elementu najblizej celu w drzewie
	//losowe przedluzenie drzewa

	//po petli
	//zbudowac sciezke cel - poczatek
	//idac od poczatku - dopoki nie ma kolizji, sprawdzamy kolejne punkty
	//kolizja - zwracamy ostatni, ktory byl OK

	delete root;
}

Vector2d RRT2::getTarget(const Vector2d & dest){
	if (getRand() < GOAL_PROB)	return dest;

	//else - generating random point on a field
	AppConfig & conf = AppConfig::instance();
	Vector2d res((conf.fieldSize.x - conf.radius) * getRand() + conf.radius,
			(conf.fieldSize.y - conf.radius) * getRand() + conf.radius);
	return res;
}

double RRT2::getRand(){
	return ((double) rand() / RAND_MAX);
}

//////////////////////////////////////////////////////////////////////////////////

Node::Node(double x, double y) : point(x,y) {

}

Node::~Node(){
	for(vector<Node *>::iterator i = children.begin(); i!=children.end(); i++)
		delete *i;
}
