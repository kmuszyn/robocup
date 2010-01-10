/*
 * GameState.cpp
 *
 *  Created on: 2009-05-12
 *      Author: Maciej Gąbka
 */

#include "GameState.h"

#include <boost/foreach.hpp>

GameState::GameState() {
	// TODO Auto-generated constructor stub

}
GameState::GameState(const GameState& gameState){
	this->ball=gameState.ball;
	this->robots=gameState.robots;
}
void GameState::updateRobotData(std::string name,Pose pos,Vector2D v,double w){
	this->robots[name]=Robot(pos,v,w);
}
void GameState::updateBallData(Vector2D pos,Vector2D v){
	this->ball=Ball(pos,v);
}
void GameState::updateSimTime(double simTime){
	this->simTime=simTime;
}

Pose GameState::getRobotPos(std::string name){
	return this->robots[name].pos;
}
Vector2D GameState::getBallPos(){
	return this->ball.pos;
}
double GameState::getSimTime(){
	return this->simTime;
}
GameState & GameState::operator=(const GameState &gameState){
	///dane dotyczace robotow
	this->robots=gameState.robots;
	///dane dotyczace pilki
	this->ball=gameState.ball;
	this->simTime=gameState.simTime;
	return *this;
}

std::ostream& operator<<(std::ostream& os,const GameState& gs){

	std::pair<std::string,GameState::Robot> robot;
	os<<"simTime "<<gs.simTime<<" ";
	BOOST_FOREACH(robot, gs.robots){
		os<<robot.first<<" "<<robot.second<<"\n";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os,const GameState::Robot& robot){

	os<<"robot position "<<robot.pos<<" linear velocity="<<robot.v<<" angular velocity="<<robot.w;
	return os;
}
GameState::~GameState() {
	// TODO Auto-generated destructor stub
}
