/*
 * RRT2.cpp
 *
 *  Created on: 2010-02-11
 *      Author: kamil
 */

#include "RRT2.h"
#include "videoServer/VideoServer.h"

RRT2::RRT2(const string & modelName) : modelName(modelName){
	// TODO Auto-generated constructor stub

}

RRT2::~RRT2() {
	// TODO Auto-generated destructor stub
}

void RRT2::plan(const Vector2d & dest, Vector2d & point){
	double treshold = 0.02;
	Position2d * robotPos = (VideoServer::instance().data())[modelName];
	//if robot already at dest point
	if ((robotPos->pos - dest).length() < treshold){
		point = dest;
		return;
	}

	//creating a tree

	//dopoki nie koniec
	//wybor punktu docelowego
	//znalezienie elementu najblizej celu w drzewie
	//losowe przedluzenie drzewa

	//po petli
	//zbudowac sciezke cel - poczatek
	//idac od poczatku - dopoki nie ma kolizji, sprawdzamy kolejne punkty
	//kolizja - zwracamy ostatni, ktory byl OK
}



Node::Node(double x, double y) : point(x,y) {

}

Node::~Node(){
	for(vector<Node *>::iterator i = children.begin(); i!=children.end(); i++)
		delete *i;
}
