/*
 * RRTPlanner.h
 *
 *  Created on: 2009-12-17
 *      Author: Maciej Gąbka
 */

#ifndef RRTPLANNER_H_
#define RRTPLANNER_H_

#include "../GameState/GameState.h"
#include "../Config/Config.h"
#include "../additional.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <limits>
#include <boost/random.hpp>


class RRTPlanner {
public:
	class RRTNode;
	typedef boost::shared_ptr <RRTNode>  RRTNodePtr;

	class RRTNode{
	public:
		RRTNode(const GameStatePtr & state_):state(state_){
			shortestDistance=std::numeric_limits<double>::infinity();
		};
		void addNode(const GameStatePtr & state){
			children.push_back(RRTNodePtr(new RRTNode(state)));
		}
		Pose getRobotPos(std::string robotName){
			return state.get()->getRobotPos(robotName);
		}
		//stan planszy w aktualnym wezle
		GameStatePtr state;
		//najkrotsza odleglosc
		double shortestDistance;
		std::list<RRTNodePtr> children;
	};
public:
	/**
	 * @brief tworzy obiekt plannera RRT
	 *
	 * @param[in] goalProb prawdopodobienstwo wyboru punktu kierujacego na cel
	 * @param[in] robotName nazwa robota dla ktorego planujemy sciezke
	 * @param[in] goalPose pozycja docelowa(razem z rotacja)
	 * @return
	 */
	RRTPlanner(double goalProb,std::string robotName,GameStatePtr currState,Pose goalPose);
	GameStatePtr getNearestState();
	GameStatePtr getNextState();
	virtual ~RRTPlanner();
private:
	/**
	 * @brief zwraca kolejny punkt docelowy.(losowy lub celu).
	 *
	 * @param[in] goalPose punkt docelowy
	 * @return
	 */
	Pose choseTarget(Pose goalPose,Pose nearestPose=Pose());
	/**
	 * @brief zwraca element poddrzewa(od currNode) znajdujacy sie najblizej celu.
	 *
	 * @param[in] targetState punkt docelowy
	 * @param[in] currNode elt poddrzewa od ktorego zaczynamy przeszukiwac
	 * @param[in] distance dotychczasowa najmniejsza odleglość
	 * @return
	 */
	RRTNodePtr findNearest(const Pose & targetPose,RRTNodePtr currNode,double distance);
	/**
	 * @brief zwraca element drzewa znajdujacy sie najblizej celu.
	 *
	 * @param[in] punkt docelowy
	 * @return
	 */
	RRTNodePtr findNearestState(const Pose & targetPose);
	/**
	 * @brief zaczynajac od zadanego stanu zwraca stan losowy.
	 *
	 * @param[in]
	 * @return
	 */
	Pose getRandomPose(Pose currentPose);
	/**
	 * @brief zwraca stan losowy losowany z rozkladem rownomiernym z przestrzeni stanow.
	 *
	 * @return
	 */
	Pose getRandomPose();
	/**
	 * @brief dokonuje ekspansji stanu w kierunku celu, zwraca stan pusty jesli nastapi kolizja
	 *
	 * @param[in] currState aktualny stan planszy
	 * @param[in] targetPose pozycja docelowa
	 * @return empty pointer is there is a collision with obstacle or new gameState extended from currState
	 */
	GameStatePtr extendState(const GameStatePtr & currState,const Pose &targetPose);
	/**
	 * @brief sprawdza czy przemieszczenie do pozycji targetPose nie spowoduje kolizji
	 *  zwraca true jesli nastapi kolizja
	 *
	 * @param[in] currState aktualny stan planszy
	 * @param[in] targetPose pozycja docelowa
	 * @return false if there is a collision with  an obstacle; true if everything is OK
	*/
	bool checkCollisions(const GameStatePtr & currState,const Pose &targetPose,bool aa=false);
 private:
	//stan od ktorego zaczynamy budowac drzewo
	RRTNodePtr root;
	//prawdopodobienstwo wyboru punktu kierujacego na cel
	double p;
	//nazwa modelu robota dla ktorego wyzanczamy punkt docelowy
	std::string robotName;
	//promień okręgu w jakim losujemy kolejny losowy stan
	static const double randomStateReach;
	//dystans jaki moze przejechac robot w kierunku celu
//	static const double robotReach;
	//pozycja docelowa robota
	const Pose goalPose;
	//stan najblizej celu
	RRTNodePtr nearest;
	//czas ostatniego uruchomienia RRT
	//mierzony w sekundach simTime
	static double lastSimTime;


};

//metoda testujaca RRT
/*
void TestRRT(){

	RRTPlanner rrtPlanner(Config::getInstance().getRRTGoalProb(),
								Config::getInstance().getTestModelName(),
										currentState,goalPose );

}*/
#endif /* RRTPLANNER_H_ */
