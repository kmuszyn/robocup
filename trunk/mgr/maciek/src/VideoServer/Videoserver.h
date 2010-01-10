#ifndef VIDEOSERVER_H_
#define VIDEOSERVER_H_


#include <boost/shared_ptr.hpp>
#include <boost/regex.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <stdio.h>

#include "../additional.h"
#include "../SimControl/SimControl.h"
#include "../GameState/GameState.h"
#include "../Logger/Logger.h"

/**
 *  @author Kamil Muszynski i Maciej Gąbka
 *  @brief klasa modelujaca funkcjonalnosc rzeczywistego programu
 *  wykorzystywanego do zwracania pozycji robotów w lidze robocub F-180
 *
 */

class Videoserver
{
//	typedef  std::map<std::string,Pose >::iterator PositionsIt;

public:
	///czas wykonania ostatniej aktualizacji, mierzony przez symulator
	double lastUpdateTime;

	Videoserver();
	~Videoserver();
	/**
	 * metoda wypelniajaca zmienna data
	 * pozycjami oraz prędkościami obiektów na planszy - gracze + pilka
	 */
	void updateGameState(GameStatePtr gameState);

};
#endif /*VIDEOSERVER_H_*/
