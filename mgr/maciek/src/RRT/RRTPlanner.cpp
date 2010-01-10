/*
 * RRTPlanner.cpp
 *
 *  Created on: 2009-12-17
 *      Author: Maciej Gąbka
 */

#include "RRTPlanner.h"

#include <algorithm>
#include <limits>
#include <sstream>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>

#include "../Logger/Logger.h"

//zasieg w jakim losujemy cel
const double RRTPlanner::randomStateReach=0.5;//[m]
//dystans jaki teoretycznie moze przejechac robot pomiedzy kolejnymi uruchomieniami RRT
//const double RRTPlanner::robotReach=0.01;//[m]
double RRTPlanner::lastSimTime;


RRTPlanner::RRTPlanner(double goalProb,std::string robotName,GameStatePtr currState,Pose goalPose_):root(new RRTNode(currState)),goalPose(goalPose_) {
	std::ostringstream log;
	log<<"starting rrt goal Pose "<<goalPose<<" and currPose "<<currState->getRobotPos(robotName);
	Logger::getInstance().LogToFile(DBG,log);

	this->p=goalProb;
	this->robotName=robotName;

	if(RRTPlanner::lastSimTime==0){
		//Logger::getInstance().LogToFile(DBG,"last sim time is 0");
		RRTPlanner::lastSimTime=currState->getSimTime();
	}else{
		double deltaTime=currState->getSimTime()-RRTPlanner::lastSimTime;
		RRTPlanner::lastSimTime=currState->getSimTime();
		log<<"rrt delta time "<<deltaTime;
		Logger::getInstance().LogToFile(DBG,log);

	}
	//double minDistance=0.01;//[m]

	double minDistance=Config::getInstance().getRRTMinDistance();
	GameStatePtr extend;
	Pose target=goalPose;

	this->nearest=root;

	//sprawdzic czy przed uruchomieniem robot nie jest w obrebie przeszkody
	if(!checkCollisions(currState,currState->getRobotPos(this->robotName),true ) ){
		Logger::getInstance().LogToFile(DBG,"collision with obstacle. Can't run RRT");
	}
	else{
		while(goalPose.distance(nearest->getRobotPos(this->robotName) ) > minDistance){

			target=this->choseTarget(goalPose);
//			log<<"chose target "<<target<<std::endl;
//			Logger::getInstance().LogToFile(DBG,log);

			nearest=findNearestState(target);

	//		log<<"find nearest state "<<nearest->getRobotPos(this->robotName)<<std::endl;
	//		Logger::getInstance().LogToFile(DBG,log);

			extend=this->extendState( nearest->state,target);

			if(extend.get()!=NULL){
				//Logger::getInstance().LogToFile(DBG,"try to add extended state");
	//			log<<"add extended state "<<extend->getRobotPos(this->robotName)<<std::endl;
	//			Logger::getInstance().LogToFile(DBG,log);

				nearest->addNode(extend);
			}
//			else{
	//			Logger::getInstance().LogToFile(DBG,"extented node is in the obstacle");
//			}

	//		getchar();
		}
	}
	log<<"end rrt result "<<nearest->getRobotPos(this->robotName)<<std::endl;
	Logger::getInstance().LogToFile(DBG,log);



}
GameStatePtr RRTPlanner::getNearestState(){
	return this->nearest->state;
}
GameStatePtr RRTPlanner::getNextState(){
//	GameStatePtr result;
	if(this->root->children.empty())
		return GameStatePtr();

	return (*( std::max_element(this->root->children.begin(),this->root->children.end(),
			boost::bind(std::less<double>(),
					boost::bind(&RRTPlanner::RRTNode::shortestDistance,_1),
					boost::bind(&RRTPlanner::RRTNode::shortestDistance,_2) ) ) ) )->state;

	//return this->nearest->state;;
}
Pose RRTPlanner::choseTarget(Pose goalPose, Pose nearestPose){
	Pose result;

	static boost::mt19937 rng(static_cast<unsigned> (time(NULL)));
	static boost::uniform_01<boost::mt19937> gen(rng);

//	Logger::getInstance().LogToFile(DBG,"another random value %f",gen());

	if(gen()<this->p)
		result=goalPose;
	else
		result=getRandomPose();
	return result;
}

RRTPlanner::RRTNodePtr RRTPlanner::findNearestState(const Pose & targetPose){
	RRTNodePtr result=this->root;
	Pose robotPose;
	double distance=numeric_limits<double>::infinity();

	BOOST_FOREACH(RRTNodePtr node,this->root->children){
		result=findNearest(targetPose,node,distance);
		if(result.get()!=NULL){
			robotPose=result->getRobotPos(this->robotName);
			distance=robotPose.distance(targetPose);
		}
	}
	return result;
}
RRTPlanner::RRTNodePtr RRTPlanner::findNearest(const Pose & targetPose,RRTNodePtr currNode,double distance){
	RRTPlanner::RRTNodePtr result;

	Pose robotPose=currNode->getRobotPos(this->robotName);
	currNode->shortestDistance=robotPose.distance(targetPose);
	result=currNode;

	//jesli wezel ma dzieci
	BOOST_FOREACH(RRTNodePtr node,currNode->children){
		RRTPlanner::RRTNodePtr nearest=findNearest(targetPose,node,distance);

		if(nearest->shortestDistance<currNode->shortestDistance){
			currNode->shortestDistance=nearest->shortestDistance;
			result=nearest;
		}
	}

/*
	//jesli jest to wezel terminalny
	if(currNode->children.empty()){
		Pose robotPose=currNode->getRobotPos(this->robotName);
		if((tmpDistance=robotPose.distance(targetPose))<distance){
			currNode->shortestDistance=tmpDistance;
			result=currNode;
//			std::cout<<"we have terminate node with pose "<<robotPose<<" distance "<<result->shortestDistance<<std::endl;
		}
	}
*/
	//std::cout<<result->shortestDistance<<std::endl;
	return result;
}
Pose RRTPlanner::getRandomPose(){
	//Pose robotPose=currentState.get()->getRobotPos(this->robotName);
	static boost::mt19937 rngX(static_cast<unsigned> (time(NULL)));
	static boost::mt19937 rngY(static_cast<unsigned> (2*time(NULL)));

	//generator wspolrzednej X
	//static boost::uniform_real<double> uni_distX(0,4);
	double maxXvalue=5.4;
	//interesujace sa jedynie pozycje rozniace sie co najwyzej o 0.01 [m]
	static boost::uniform_int<int> uni_distX(0,maxXvalue*100);


//	static boost::variate_generator<boost::mt19937, boost::uniform_real<double> >
	static boost::variate_generator<boost::mt19937, boost::uniform_int<int> >
	genX(rngX, uni_distX);

	//generator wspolrzednej Y
//	static boost::uniform_real<double> uni_distY(0,4);
	double maxYvalue=7.4;
	//interesujace sa jedynie pozycje rozniace sie co najwyzej o 0.01 [m]
	static boost::uniform_int<int> uni_distY(0,maxYvalue*100);

	//static boost::variate_generator<boost::mt19937, boost::uniform_real<double> >
	static boost::variate_generator<boost::mt19937, boost::uniform_int<int> >
	genY(rngY, uni_distY);
	double x=genX();
	double y=genY();
	Pose randomPose(x/100.0,y/100.0,0.0);
//	std::ostringstream log;
//	log<<"randomPose "<<randomPose;
//	Logger::getInstance().LogToFile(DBG,log);
	return randomPose;

}
Pose RRTPlanner::getRandomPose(Pose currentPose){
	Pose robotPose=currentPose;
	//Pose robotPose=currentState.get()->getRobotPos(this->robotName);
	static boost::mt19937 rng(static_cast<unsigned> (time(NULL)));

	//generator wspolrzednej X
	static boost::normal_distribution<double> distX(robotPose.get<0>(),RRTPlanner::randomStateReach);
	boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> >  genX(rng, distX);

	//generator wspolrzednej Y
	static boost::normal_distribution<double> distY(robotPose.get<1>(),RRTPlanner::randomStateReach);
	boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> >  genY(rng, distY);

//	GameStatePtr result(new GameState((*currentState)));

	//std::cout<<"X="<<genX()<<"Y="<<genY()<<std::endl;

//	result->updateRobotData(this->robotName,Pose(genX(),genY(),robotPose.get<2>()));
//	return result;

	return Pose(genX(),genY(),robotPose.get<2>());
}

GameStatePtr RRTPlanner::extendState(const GameStatePtr & currState,const Pose& targetPose){

	assert(currState.get()!=NULL);

	//TODO: rozwazyc sprawdzenie czy targetPose nie lezy w obrebie przeszkody

	std::ostringstream log;
//	log<<"try extend state to "<<targetPose<<std::endl;
//	Logger::getInstance().LogToFile(DBG,log);


	GameStatePtr result( new GameState(*currState));
	Pose currPose=currState->getRobotPos(this->robotName);

//	std::cout<<"extend state currState "<<*currState<<std::endl;

	//wyznacz rownanie prostej laczacej stan biezacy z docelowym

	//jesli jest to prosta typu x=A
	if( fabs(currPose.get<0>()-targetPose.get<0>() ) < 0.001 ){
		result->updateRobotData(this->robotName,
				Pose(currPose.get<0>(),currPose.get<1>()+Config::getInstance().getRRTRobotReach(),currPose.get<2>())
				);
	}
	else{

		double xA=currPose.get<0>();
		double yA=currPose.get<1>();

		double xB=targetPose.get<0>();
		double yB=targetPose.get<1>();

		//wsp kierunkowy prostej
		double a=(yB-yA)/(xB-xA);

		//przesuniecie
		double b=yA - xA*a;

		double delta = /*4*/( pow( a*(b - yA) - xA,2 ) - (1+pow(a,2))*(pow(xA,2)+ pow((b-yA),2) -
				pow(Config::getInstance().getRRTRobotReach(),2) ) );

		assert(delta>0);

		double x1=( xA-a*(b-yA)-sqrt(delta) )/(1+pow(a,2));
		double x2=( xA-a*(b-yA)+sqrt(delta) )/(1+pow(a,2));

/*		double y1=a*x1 +b;
		double y2=a*x2 +b;
		std::cout<<"x1="<<x1<<" y1="<<y1<<std::endl;
		std::cout<<"x2="<<x2<<" y2="<<y2<<std::endl;
*/
		double x,y;

		if(targetPose.get<0>() > currPose.get<0>()){
			x=std::max(x1,x2);
			y=a*x+b;
		}
		else{
			x=std::min(x1,x2);
			y=a*x+b;
		}

		result->updateRobotData(this->robotName,
						Pose(x,y,currPose.get<2>())
						);
		//TODO: rozwazyc sytuacje ze cel jest blizej niz RRT::RobotReach;
	}
	Pose resultPose=result->getRobotPos(this->robotName);
	double test=pow(resultPose.get<0>()-currPose.get<0>(),2)+pow(resultPose.get<1>()-currPose.get<1>(),2);
	//test poprawnosci rozwiazania
	assert(fabs(pow(Config::getInstance().getRRTRobotReach(),2)-test)<0.001);

	//czy ten punkt nie lezy w obrebie przeszkody
	if(!checkCollisions(currState,resultPose)){
		return GameStatePtr();
	}

//	Logger::getInstance().LogToFile(DBG,"ending extend state");
	return result;
}
bool RRTPlanner::checkCollisions(const GameStatePtr & currState,const Pose &targetPose,bool aa){

	Pose obstaclePose;
	const std::vector<std::string> blueTeam=Config::getInstance().getBlueTeam();
	std::ostringstream log;

//	log<<"checking for collision for target"<<targetPose;
//	Logger::getInstance().LogToFile(DBG,log);

	double robotRadius=Config::getInstance().getRRTRobotRadius();
	if(aa)
		robotRadius-=0.2;
	BOOST_FOREACH(std::string modelName,blueTeam){
		if(modelName.compare(this->robotName)!=0){
			obstaclePose=currState->getRobotPos(modelName);

//			log<<"obstacle name"<<modelName<<"Pose"<<obstaclePose<<std::endl;
//			Logger::getInstance().LogToFile(DBG,log);

			//sprawdz czy cel nie lezy w obrebie przeszkody
			if(  pow(targetPose.get<0>()-obstaclePose.get<0>(),2) + pow(targetPose.get<1>()-obstaclePose.get<1>(),2) <=
					pow(robotRadius,2) ){
//				log<<"target "<<targetPose<<". collision with blue team modelName="<<modelName;
//				Logger::getInstance().LogToFile(DBG,log);
				return  false;
			}
		}
	}
//	Logger::getInstance().LogToFile(DBG,"start extend state2");
/*
	//	std::cout<<"extend state2"<<std::endl;

	const std::vector<std::string> redTeam=Config::getInstance().getRedTeam();
	BOOST_FOREACH(std::string modelName,redTeam){
		if(modelName.compare(this->robotName)!=0){
			obstaclePose=currState.get()->getRobotPos(modelName);
			if( ( pow(obstaclePose.get<0>()-targetPose.get<0>(),2) + pow(obstaclePose.get<1>()-targetPose.get<1>(),2) )<0.1){
				return  false;
			}
		}
	}

*/
	return true;
}
RRTPlanner::~RRTPlanner() {
	// TODO Auto-generated destructor stub
}
