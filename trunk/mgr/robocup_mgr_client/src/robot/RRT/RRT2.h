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
	/**
	 * Returns random target - either dest or a random point on the field
	 */
	Vector2d getTarget(const Vector2d & dest);

	/**
	 * Returns rand 0..1, srand() should be called first!
	 */
	double getRand();

private:
	/// Minimum distance to target to stop algorith
	static const double THRESHOLD = 0.2;

	///Probability of expanding tree towards destination
	static const float GOAL_PROB = 0.4;

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
