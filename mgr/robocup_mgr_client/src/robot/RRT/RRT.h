/*
 * RRT.h
 *
 *  Created on: 2009-05-10
 *      Author: kamil
 */

#ifndef RRT_H_
#define RRT_H_

#include "RRTTree.h"
#include "util/vector2d/Vector2d.h"
#include "gameState/GameState.h"

#include "videoServer/VideoServer.h"

#include <string>
#include <cstdlib>

/**
 * Klasa realizująca algorytm wyszukiwania ścieżki i unikania kolizji
 * RRT (Rapidly-exploring random trees).
 *
 * Na podstawie: Real-time randomized path planning for
 * robot navigation (James Bruce, Manuela Veloso)
 */
class RRT {
public:
	RRT(std::string modelName);
	~RRT();

	Vector2d plan(Vector2d goal);
	Vector2d extend(Vector2d begin, Vector2d goal);

private:
	Vector2d chooseTarget(Vector2d goal);
	Vector2d randomTarget();
	bool checkCollisions(const Vector2d & point);


	float getRand();

	RRTTree * rrttree;
	std::string modelName;

	//ustawienie stałych algorytmu
	//TODO: pobieranie tych parametrów z pliku
	static const float GOAL_PROB = 0.4;
};

#endif /* RRT_H_ */
