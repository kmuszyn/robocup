/*
 * RRTTree.h
 *
 *  Created on: 2009-05-10
 *      Author: kamil
 */

#ifndef RRTTREE_H_
#define RRTTREE_H_

#include "../../util/vector2d/Vector2d.h"
#include "../../gameState/GameState.h"
#include <vector>
#include <fstream>
#include <ios>
#include <iostream>

class RRTTreeNode;

class RRTTree {

public:
	RRTTree();
	RRTTree(Vector2d startPos);
	~RRTTree();

	RRTTreeNode * addNode(Vector2d pos, RRTTreeNode * parent);
	RRTTreeNode * getRoot();

	RRTTreeNode * findNearest(Vector2d target);

	void display();
	void display_(RRTTreeNode * node, int level);

	void print2tex(const Vector2d & start, const Vector2d & end, GameState * gameStatePtr);
	void print2tex_(RRTTreeNode * node, std::ofstream & file);

private:
	RRTTreeNode * root;

	//do rekurencyjnego przeszukiwania drzewa
	RRTTreeNode * findNearest(RRTTreeNode * node, const Vector2d & target);


};

//////////////////////////////////////////////////////////////////////////////

class RRTTreeNode{
public:
	RRTTreeNode(Vector2d pos, RRTTreeNode * parent);

	Vector2d position;
	/////////////////////////////////////
	RRTTreeNode * parent;
	std::vector<RRTTreeNode *> children;
};

#endif /* RRTTREE_H_ */
