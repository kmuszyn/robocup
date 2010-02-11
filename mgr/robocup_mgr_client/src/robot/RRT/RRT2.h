/*
 * RRT2.h
 *
 *  Created on: 2010-02-11
 *      Author: kamil
 */

#ifndef RRT2_H_
#define RRT2_H_

#include <string>
#include <vector>
#include "util/vector2d/Vector2d.h"
#include "util/position2d/Position2d.h"

/**
 * This is a second implementation of RRT algorithm, faster, better and so on :)
 *
 */
using namespace std;

class RRT2 {
public:
	/**
	 * Inits planner.
	 * @param modelName model for which planning is done, used also to skip it in collision
	 * detection
	 */
	RRT2(const string & modelName);
	/**
	 * Removes rrttree from memory
	 */
	~RRT2();

	/**
	 * Plans path.
	 * @param dest Destination
	 * @param point Point a robot should go to, filled by planner
	 */
	void plan(const Vector2d & dest, Vector2d & point);

private:
	const string & modelName;
};

class Node{
public:
	Node(double x, double y);
	~Node();
public:
	Node * parent;
	vector<Node *> children;
	Vector2d point;
};

#endif /* RRT2_H_ */
