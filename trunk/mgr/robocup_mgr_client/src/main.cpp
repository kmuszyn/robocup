//--- logging ---
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/logger.h"
//---------------

#include "gameState/GameState.h"
#include "robot/Robot.h"

//#include <sstream>

#include <math.h>

#include <time.h>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>

#include "videoServer/VideoServer.h"



log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("main"));



int main(int argc, char *argv[]){
	////// start generatora liczb losowych ////
	srand(time(0) + getpid());				///
	///////////////////////////////////////////

	//if (argc==1 && strcmp(argv[1],"-d")==0)
	log4cxx::PropertyConfigurator::configure("../config/log4cxx.properties");



	VideoServer::instance().update();

	while(true){
		VideoServer::instance().update();
		VideoServer::instance().display();
	}




//
//	RRTTree rrtTree;
//
//	rrtTree.addNode(Vector2d(0,0), 0);
//	rrtTree.addNode(Vector2d(2,3), rrtTree.getRoot());
//	RRTTreeNode * tmp = rrtTree.addNode(Vector2d(1,0), rrtTree.getRoot());
//	rrtTree.addNode(Vector2d(2,1), tmp);
//	rrtTree.addNode(Vector2d(2,2), tmp);
//
//	RRTTreeNode * node = rrtTree.findNearest(Vector2d(3,3));
//	std::cout<<"Nearest: \n";
//	std::cout<<node->position<<std::endl;






	/*GameState gameState("../config/models.xml");
	gameState.update();
	gameState.display();

	std::cout<<"Robot r:\n";
	Robot r("omni_red0",TEAM_1, &gameState);

	LOG4CXX_DEBUG(logger, "( ** START ** ) ");
	LOG4CXX_DEBUG(logger, "Start time: "<< SimControl::getInstance().getSimTime());

	while(true){
		//update stanu gry
		if (gameState.update())
//		gameState.display();



		r.doTest();
//		else
		usleep(100);


		//w zaleznosci od stanu gry -> decyzje arbitra
			//gol -> restart
			//aut -> ustawienie pilki itp

		//algorytm robota, oceniajacy stan gry i obliczajacy mozliwe posuniecia
		//dla kazdego z robotow z mojej druzyny - > obliczanie ruchow

		//ruch robotow przeciwnika



	}*/
}

//lista rzeczy do zrobienia:
/*
TODO: testowanie algorytmu unikania kolizji

*/
