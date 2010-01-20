/*
 * RRTTree.cpp
 *
 *  Created on: 2009-05-10
 *      Author: kamil
 */

#include "RRTTree.h"

#include <boost/assert.hpp>

RRTTree::RRTTree() {
	this->root = 0;
}

RRTTree::RRTTree(Vector2d startPos){
	this->root = new RRTTreeNode(startPos, 0);
}

RRTTree::~RRTTree() {
	// TODO Auto-generated destructor stub
}


RRTTreeNode * RRTTree::addNode(Vector2d pos, RRTTreeNode * parent){
	RRTTreeNode * node = new RRTTreeNode(pos, parent);

	if (parent==0)
		root = node;
	else
		parent->children.push_back(node);

	return node;
}


RRTTreeNode * RRTTree::getRoot(){
	return root;
}


RRTTreeNode * RRTTree::findNearest(Vector2d target){
	BOOST_ASSERT(this->root != 0);

	if (this->root->children.size() == 0)
		return this->root;

	//w p.p znajdujemy dla kazdego z poddrzew element najblizszy do zadanego

	double minDist = (this->root->position - target).length();
	RRTTreeNode * result = this->root;

	std::vector<RRTTreeNode * >::iterator ii = this->root->children.begin();

	for(; ii!= this->root->children.end(); ii++){

		RRTTreeNode * tmpNode = findNearest(*ii, target);
		double tmpNodeDist = (tmpNode->position - target).length();
		if (tmpNodeDist < minDist){
			minDist = tmpNodeDist;
			result = tmpNode;
		}
	}

	return result;
}

RRTTreeNode * RRTTree::findNearest(RRTTreeNode * node,  const Vector2d & target){
	//dla kazdego z potomkow znajdujemy najblizszy targetowi node

//	std::cout<<"W węźle: "<<node->position<<std::endl;

	double nearestDistance = (node->position - target).length();
	RRTTreeNode * nearest = node;

	if (node->children.size() == 0) {
//		std::cout<<"Brak dzieci\n";
	} else { //nie jest lisciem, wiec znajdujemy jego najblizszy node

		std::vector<RRTTreeNode *>::iterator ii = node->children.begin();
		for (; ii != node->children.end(); ii++) {
			RRTTreeNode * tmpNode = findNearest(*ii, target);
			double tmpDist = (tmpNode->position - target).length();
			if (tmpDist < nearestDistance) {
				nearestDistance = tmpDist;
				nearest = tmpNode;
			}
		}
	}
	return nearest;
}

void RRTTree::display(){
	std::cout<<"TREE:\n";
	std::cout<<"root: "<<this->root->position<<std::endl;
	std::vector<RRTTreeNode *>::iterator ii = this->root->children.begin();
	for (; ii != this->root->children.end(); ii++) {
		this->display_((*ii), 1);
	}
}


void RRTTree::display_(RRTTreeNode * node, int level){
	for(int i = 0; i< level; i++)
		std::cout<<" ";

	std::cout<<node->position<<std::endl;
	std::vector<RRTTreeNode *>::iterator ii = node->children.begin();
	for (; ii != node->children.end(); ii++) {
		this->display_((*ii), level+1);
	}
}

void RRTTree::print2tex(const Vector2d & start, const Vector2d & end, GameState * gameStatePtr){
	double s = 100.0; //skala
	std::ofstream file;
	file.open("drzewo.tex",std::ios::out);
	file.precision(3);
//nagłówki
	file<<"\\documentclass[onecolumn,a4paper]{minimal}"<<std::endl;
	file<<"\\usepackage[left=0.5cm,top=1.5cm,right=0.5cm,bottom=0.5cm,includehead,includefoot]{geometry}"<<std::endl;
	file<<"\\usepackage[usenames]{color}"<<std::endl;
	file<<"\\definecolor{orange}{rgb}{1,0.5,0}"<<std::endl;
	file<<"\\begin{document}"<<std::endl;
	file<<"\\begin{picture}(540,740)(0,0)"<<std::endl;
	file<<"{"<<std::endl;
	file<<"\\color{black}"<<std::endl;
	file<<"\\linethickness{0.5mm}"<<std::endl;
//	boisko
	file<<"	\\put(0,0){\\line(1,0){540}}"<<std::endl;
	file<<"\\put(0,0){\\line(0,1){740}}"<<std::endl;
	file<<"\\put(0,740){\\line(1,0){540}}"<<std::endl;
	file<<"\\put(540,0){\\line(0,1){740}}"<<std::endl;
	file<<"}"<<std::endl;
//	start i koniec
	file<<"{"<<std::endl;
	file<<"\\color{red}"<<std::endl;
	file<<"\\put("<<start.x * s<<","<<start.y*s<<"){\\circle*{5}}"<<std::endl;
	file<<"\\color{blue}"<<std::endl;
	file<<"\\put("<<end.x * s<<","<<end.y*s<<"){\\circle*{5}}"<<std::endl;
	file<<"}"<<std::endl;
//	wezly drzewa

	if ((this->root!=0) && this->root->children.size()>0){
		std::vector<RRTTreeNode *>::iterator ii = this->root->children.begin();
		for (; ii != this->root->children.end(); ii++) {
			this->print2tex_((*ii), file);
		}
	}
//	roboty

	std::map<std::string, Position2d*>::iterator ii = gameStatePtr->getModels()->begin();
	for(;ii!=gameStatePtr->getModels()->end(); ii++){
		file<<"\\put("<<ii->second->pos.x * s<<","<<ii->second->pos.y*s<<"){\\circle{9}}"<<std::endl;
	}

//	\put(20,30){\circle*{5}}
//	\put(20,40){\circle*{3}}
//
	file<<"\\end{picture}"<<std::endl;
	file<<"\\end{document}"<<std::endl;

	file.close();
}

void RRTTree::print2tex_(RRTTreeNode * node, std::ofstream & file){
	double s = 100.0;
	file<<"\\put("<<node->position.x * s<<","<<node->position.y*s<<"){\\circle*{2}}"<<std::endl;
	if (node->children.size()>0){
		std::vector<RRTTreeNode *>::iterator ii = node->children.begin();
		for (; ii != node->children.end(); ii++) {
			this->print2tex_((*ii), file);
		}
	}
}

#ifdef MGR_VIEWER
int RRTTree::countNodes(){
	return root->countNodes();
}

void RRTTree::writeViewerData(std::ofstream & s){
	root->writeViewerData(s);
}

#endif

/////////////////////// RRTTreeNode //////////////////////////////////

RRTTreeNode::RRTTreeNode(Vector2d pos, RRTTreeNode * parent){
	this->position = pos;
	this->parent = parent;
}

#ifdef MGR_VIEWER
int RRTTreeNode::countNodes(){
	int result = 1; //this node
	if (children.size()>0){
		std::vector<RRTTreeNode *>::iterator ii = children.begin();
		for (; ii != children.end(); ii++) {
			result += (*ii)->countNodes();
		}
	}

	return result;
}

void RRTTreeNode::writeViewerData(std::ofstream & s){

	s<<position.x<<" "<<position.y<<std::endl;

	if (children.size()>0){
		std::vector<RRTTreeNode *>::iterator ii = children.begin();
		for (; ii != children.end(); ii++) {
			(*ii)->writeViewerData(s);
		}
	}
}
#endif
