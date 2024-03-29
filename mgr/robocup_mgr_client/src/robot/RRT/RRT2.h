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
#include <map>
#include "util/vector2d/Vector2d.h"
#include "util/position2d/Position2d.h"


/**
 * This is a second implementation of RRT algorithm, faster, better and so on :)
 *
 */
using namespace std;

class Node;

class RRT2 {
public:
	/**
	 * Inits planner.
	 * @param robotName model for which planning is done, used also to skip it in collision
	 * detection
	 */
	RRT2(const string & robotName);
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


	/**
	 * Stores data in file for MGR_VIEWER
	 * format:
	 * :rrt (nodesCount)
	 * x y (of a node)
	 * x y
	 * ...
	 */
	void writeViewerData(const Node * root, const Vector2d & result);


private:
	/// Minimum distance to target to stop algorithm
	static const double THRESHOLD = 0.1;

	///Probability of expanding tree towards destination
	static const float GOAL_PROB = 0.6;

	///Distance used to add new nodes, calculated in constructor method
	double extendDistance;

	const string & robotName;
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Node{
public:
	Node(double x, double y);
	~Node();

	///adds a child to current node
	void addChild(Node * child);

	///returns pointer to the node nearest to target
	Node * findNearest(const Vector2d & target);

	/**
	 * Generates a node wich extends tree towards target starting from this node,
	 * collisions are not checked here!
	 */
	Node * extend(const double distance, const Vector2d & target);

	/**
	 * Writes node data to given file.
	 */
	void writeViewerData(ofstream & file) const;

public:
	Node * parent;
	vector<Node *> children;
	Vector2d point;

	static int nodesCounter;
};

#endif /* RRT2_H_ */
