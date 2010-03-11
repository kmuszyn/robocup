/*
 * RRT2.cpp
 *
 *  Created on: 2010-02-11
 *      Author: kamil
 */

#include "RRT2.h"
#include "videoServer/VideoServer.h"
#include "util/geom/Geom.h"
#include <list>

int Node::nodesCounter = 0;

RRT2::RRT2(const string & robotName) : robotName(robotName){
	extendDistance = AppConfig::instance().radius / 2.0;
	Node::nodesCounter = 0;
}

RRT2::~RRT2() {
	//cout<<"RRT2 destructor, nodes counter: "<<Node::nodesCounter<<endl;
}

void RRT2::plan(const Vector2d & dest, Vector2d & result){
	/*
	 * This method is divided into 4 parts:
	 * 1. Checking, if robot arleady is at given (dest)
	 * 2. Generating possible obstacle list
	 * 3. Checking, if there is a straigth obstacle-free path to target, so planning could be avoided
	 * 4. If not, creating a RRT tree
	 * 5. Creating path from RRT tree
	 * 6. Simplifying path
	 */

//	cout<<"Planning start ****************************************\n";

	// 1. Checking if dest is not reached

	Position2d * robotPos = (VideoServer::instance().data())[robotName];
	//if robot already at dest point
	if ((robotPos->pos - dest).length() < THRESHOLD){
		result = dest;
		cout<<"Robot at place!\n";
		return;
	}

	// 2. Generating obstacle list

//	cout<<"Generating obstacles\n";

	list<Vector2d> obstacles;
	std::map<std::string, Position2d*>::iterator ii =
			VideoServer::instance().data().begin();
	for (; ii != VideoServer::instance().data().end(); ii++) {
		if (ii->first == AppConfig::instance().ball) continue;
		if (ii->first == robotName) continue;
		obstacles.push_back(ii->second->pos);
//		cout<<"Adding: "<<ii->second->pos<<endl;
	}

	//cout << "Obstacles: "<<obstacles.size()<<endl;

	// 3. Looking for obstacle-free straight path

//	cout<<"Checking path to target\n";
	if (Geom::isPathClear(robotPos->pos, dest, obstacles)){
		result = dest;
		//cout<<"Path clear, exit\n";
		return;
	}

	// 4. Planning using RRT tree: creating a tree

//	cout<<"Rrt plannin start\n";

	Node * root = new Node(robotPos->pos.x, robotPos->pos.y);
	Node * nearest = root;
	//sort obstacles in distance order, for fast collision check
	//used by node->extend()

	//while dest point not reached
	while(true){
		Vector2d target = getTarget(dest);
		nearest = root->findNearest(target);
		//if tree reached target point, break loop
		if ((nearest->point - dest).length() < THRESHOLD) break;

		//if max node count reached
		if (Node::nodesCounter > 200) break;

		//else, keep expanding
		Node * tmp = nearest->extend(extendDistance, target);
		//checking collision here!
		bool collides = Geom::pointCollides(tmp->point, obstacles);
		if (!collides)
			nearest->addChild(tmp);
		else
			delete tmp;
	}

//	cout<<"Tree size: "<<Node::nodesCounter<<endl;

//	cout<<"Creating path:\n";

	// 5. Creating path from RRT tree (from nearest to first (without root!) element)
	list<Node *> path;
	Node * tmp = nearest;
	while(tmp->parent->parent != 0){
//		cout<<"Adding: "<<tmp->point<<endl;
		path.push_front(tmp);
		tmp = tmp->parent;
	}

	result = path.front()->point;

	// 6. Simplifying path

	// Idea is that robot should go to the first point in the path,
	// to which there is a straigh obstacle-free line

//	cout<<"Simplyfing path\n";
	for(list<Node *>::iterator i = path.begin(); i!= path.end(); i++){
//		cout<<(*i)->point<<endl;
		if (Geom::isPathClear(robotPos->pos, (*i)->point, obstacles))
			result = (*i)->point;
		else
			break;
	}

	// 7. Saving results to file MGR_VIEWER
#ifdef MGR_VIEWER
	this->writeViewerData(root, result);
#endif
//	cout<<"Result after simplyfing: "<<result<<endl;


	//cout<<"Result: "<<result<<endl;


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

void RRT2::writeViewerData(const Node * root, const Vector2d & result){
	string debugFile = robotName + ".txt";
	ofstream file;
	file.open(debugFile.c_str(),ios::app);
	file<<":rrt "<<Node::nodesCounter<<endl;
	if (root != 0){
		root->writeViewerData(file);
	}
	file<<":rrtresult "<<result.x<<" "<<result.y<<endl;
	file.close();
}

//////////////////////////////////////////////////////////////////////////////////

Node::Node(double x, double y) : point(x,y) {
	parent = 0;
	nodesCounter++;
}

Node::~Node(){
	for(vector<Node *>::iterator i = children.begin(); i!=children.end(); i++)
		delete *i;
	nodesCounter--;
}

Node * Node::findNearest(const Vector2d & target){
	double minDist = (point - target).length();
	Node * nearest = this;
	Node * tmp;
	double tmpDist;
	for (vector<Node *>::iterator i = children.begin(); i != children.end(); i++){
		tmp = (*i)->findNearest(target);
		tmpDist = (tmp->point - target).length();
		if (tmpDist < minDist){
			minDist = tmpDist;
			nearest = tmp;
		}
	}
	return nearest;
}

Node * Node::extend(const double distance, const Vector2d & target){
	//new point calculation
	double length = (target-point).length();
	double cosAlfa = (target.x - point.x) / length;
	double sinAlfa = (target.y - point.y) / length;

	Node * tmp = new Node( (distance * cosAlfa) + point.x, (distance * sinAlfa) + point.y );
	return tmp;
}

void Node::addChild(Node * child){
	child->parent = this;
	children.push_back(child);
}

void Node::writeViewerData(ofstream & file) const {
	file<<point.x<<" "<<point.y<<endl;
	for (vector<Node *>::const_iterator i = children.begin(); i != children.end(); i++)
		(*i)->writeViewerData(file);
}
