//--- logging ---
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/logger.h"
//---------------

#include "gameState/GameState.h"
#include "robot/Robot.h"
#include "AI/AI.h"

//#include <sstream>

#include <math.h>

#include <time.h>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>

#include "videoServer/VideoServer.h"


//remove this
#include "robot/RRT/RRT2.h"

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("main"));




int main(int argc, char *argv[]){
	////// start generatora liczb losowych ////
	srand(time(0) + getpid());				///
	///////////////////////////////////////////

	//if (argc==1 && strcmp(argv[1],"-d")==0)
	log4cxx::PropertyConfigurator::configure("../config/log4cxx.properties");


	//AI robotAI2(AppConfig::instance().team2[0], TEAM2);
	VideoServer::instance().update();
	Robot red0(AppConfig::instance().team1[0], TEAM1);
	Robot red1(AppConfig::instance().team1[1], TEAM1);
	Robot red2(AppConfig::instance().team1[2], TEAM1);
	Robot red3(AppConfig::instance().team1[3], TEAM1);

	Robot blue0(AppConfig::instance().team2[0], TEAM2);
	Robot blue1(AppConfig::instance().team2[1], TEAM2);
	Robot blue2(AppConfig::instance().team2[2], TEAM2);
	Robot blue3(AppConfig::instance().team2[3], TEAM2);

	while(true){
		//cout<<"Update\n";
		VideoServer::instance().update();
	//	VideoServer::instance().display();


		red0.makeMove();
//		red1.makeMove();
//		red2.makeMove();
//		red3.makeMove();
//
//
//		blue0.makeMove();
//		blue1.makeMove();
//		blue2.makeMove();
//		blue3.makeMove();

		/*Vector2d dest(2,2);
		Vector2d res;
		std::cout<<"Planning start\n";
		clock_t t1 = clock();
		for (long i = 0; i < 1000000; i++){
			RRT2 rrt2(AppConfig::instance().team1[0]);
			rrt2.plan(dest, res);
		}

		clock_t t2 = (double) clock() - t1;

		std::cout<<"Time: "<<(double)t2 / CLOCKS_PER_SEC<<std::endl;*/

	}

	cout<<"While is broken\n";


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
