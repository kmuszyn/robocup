#include "Videoserver.h"
#include "../Config/Config.h"

Videoserver::Videoserver()
{
#ifdef GAZEBO
	lastUpdateTime = SimControl::getInstance().getSimTime();
#endif
}

Videoserver::~Videoserver()
{
	// dodac usuwanie z positions?
}

void Videoserver::updateGameState(GameStatePtr gameState) {
	double currTime;
#ifdef GAZEBO
	currTime = SimControl::getInstance().getSimTime();
#endif
	gameState->updateSimTime(currTime);
	//okres czasu od ostatniego update
	double updateT = currTime - this->lastUpdateTime;
	this->lastUpdateTime = currTime;

	std::map<std::string,Pose > positions;
#ifdef GAZEBO
	SimControl::getInstance().getAllPos(positions);
#endif
	PositionsIt ii=positions.begin();
	Vector2D v;
	for(;ii!=positions.end();++ii){
		Pose tmp_pos((*ii).second);
		std::string model_name=(*ii).first;
		tmp_pos -= gameState->getRobotPos(model_name);
		tmp_pos.get<2>()=convertAnglePI(tmp_pos.get<2>());
		tmp_pos*=(1/updateT);
		Vector2D v(tmp_pos.get<0>(),tmp_pos.get<1>());
		gameState->updateRobotData(model_name,(*ii).second,v,tmp_pos.get<2>());
		double w=tmp_pos.get<2>();
		if(model_name.compare(Config::getInstance().getTestModelName())==0){
			double vel=sqrt(pow(v.x,2)+pow(v.y,2));
			Logger::getInstance().LogToFile(PATH,"from videoserwer name=%s\t deltaT=%lf\t x=%lf\t y=%lf\t vx=%lf\t vy=%lf\t v=%lf\t w=%lf,"
					,model_name.c_str(),updateT,(*ii).second.get<0>(),(*ii).second.get<1>(),v.x,v.y ,vel,w);
		}
	}


}
/*
void Videoserver::InitPrint(std::ofstream & file,std::string fileName,std::string robotName)
{
	double s = 100.0; //skala
	file.open(fileName.c_str(),std::ios::app);
	file.setf(std::ios::fixed);
	file.precision(3);

	file<<"\\begin{picture}"<<Vector2D(Field::EFFECTIVE_SIZE)*s<<"\n";
	//rysowanie boiska
	file<<"\\thicklines\n";
	file<<"\\put(0,0){\\line(0,1){"<<Field::EFFECTIVE_SIZE.y*s<<"}}\n";
	file<<"\\put(0,0){\\line(1,0){"<<Field::EFFECTIVE_SIZE.x*s<<"}}\n";
	file<<"\\put(0,"<<Field::EFFECTIVE_SIZE.y*s<<"){\\line(1,0){"<<Field::EFFECTIVE_SIZE.x*s<<"}}\n";
	file<<"\\put("<< Field::EFFECTIVE_SIZE.x*s <<",0){\\line(0,1){"<<Field::EFFECTIVE_SIZE.y*s<<"}}\n\n";
	file<<"\\thinlines\n";

	file<<"\\put"<< Vector2D(Field::BOTTOM_LEFT)*s <<"{\\line(1,0){"<<Field::AREA_SIZE.x*s<<"}}\n";
	file<<"\\put"<< Vector2D(Field::BOTTOM_LEFT)*s <<"{\\line(0,1){"<<Field::AREA_SIZE.y*s<<"}}\n";
	file<<"\\put"<< Vector2D(Field::TOP_RIGHT)*s <<"{\\line(-1,0){"<<Field::AREA_SIZE.x*s<<"}}\n";
	file<<"\\put"<< Vector2D(Field::TOP_RIGHT)*s <<"{\\line(0,-1){"<<Field::AREA_SIZE.y*s<<"}}\n";
	file<<"\\put"<< Vector2D(Field::CENTER)*s <<"{\\line(1,0){"<<Field::AREA_SIZE.x*s/2.0<<"}}\n";
	file<<"\\put"<< Vector2D(Field::CENTER)*s <<"{\\line(-1,0){"<<Field::AREA_SIZE.x*s/2.0<<"}}\n";
	file<<"\\put"<< Vector2D(Field::CENTER)*s <<"{\\line(0,1){2}}\n";
	file<<"\\put"<< Vector2D(Field::CENTER)*s <<"{\\line(0,-1){2}}\n\n";

}
void Videoserver::Print(std::ofstream& file,std::string robotName)
{
	double s = 100.0; //skala
	//pilka

		Vector2D ball_pos = Videoserver::data.getPosition("ball") * s;
		file<<"\\color{orange}\n";
		file<<"\\put"<<ball_pos<<"{\\circle*{"<< 0.04 * s<< "}}\n";
		file<<"\\color{black}\n\n";

	//robot poruszajacy sie
	{
	Vector2D robot_pos = Videoserver::data.getPosition(robotName) * s;
	file<<"\\color{blue}\n";
	file<<"\\put"<<robot_pos<<"{\\circle*{1.2}}\n";
	file<<"\\color{black}\n\n";
	}


	file<<"%Przeszkody:\n";
	strvec names = Names::getNames();
	strvec::iterator ii;

	for(ii = names.begin(); ii!=names.end(); ii++){
		std::string name = *ii;
		if(name.compare("ball")!=0 && name!=robotName){
			//pozycja przeszkody w ukladzie z plansza
			Vector2D tmp=Videoserver::data.getPosition(name) * s;;
			file<<"\\put"<<tmp<<"{\\circle*{1.2}}\n";

		}
	}
}
void Videoserver::FiniPrint(std::ofstream& file,std::string robotName)
{
	double s = 100.0; //skala
	//pilka

		Vector2D ball_pos = Videoserver::data.getPosition("ball") * s;
		file<<"\\color{orange}\n";
		file<<"\\put"<<ball_pos<<"{\\circle*{"<< 0.04 * s<< "}}\n";
		file<<"\\color{black}\n\n";

		/
	//robot poruszajacy sie
	{
	Vector2D robot_pos = Videoserver::data.getPosition(robotName) * s;
	file<<"\\color{blue}\n";
	file<<"\\put"<<robot_pos<<"{\\circle*{5}}\n";
	//The letter k stands for the following value: 0.5522847498 r
	double r=CVM::L*s;
	double k=0.5522847498*r;
	double x=robot_pos.x;
	double y=robot_pos.y;
	file<<"\\cbezier("<<x-r<<","<<y<<")("<<x-r<<","<<y+k<<")("<<x-k<<","<<y+r<<")("<<x<<","<<y+r<<")\n";
	file<<"\\cbezier("<<x<<","<<y+r<<")("<<x+k<<","<<y+r<<")("<<x+r<<","<<y+k<<")("<<x+r<<","<<y<<")\n";
	file<<"\\cbezier("<<x+r<<","<<y<<")("<<x+r<<","<<y-k<<")("<<x+k<<","<<y-r<<")("<<x<<","<<y-r<<")\n";
	file<<"\\cbezier("<<x<<","<<y-r<<")("<<x-k<<","<<y-r<<")("<<x-r<<","<<y-k<<")("<<x-r<<","<<y<<")\n";
	//file<<"\\put"<<robot_pos<<"{\\circle{"<<2.0*s*CVM::L<<"}}\n";
	//file<<"\\thicklines\n";
	//file<<"\\put"<<robot_pos<<"{\\vector(0,1){30}}\n";
	file<<"\\color{black}\n\n";
	}

**
	file<<"%Przeszkody:\n";
	strvec names = Names::getNames();
	strvec::iterator ii;

	for(ii = names.begin(); ii!=names.end(); ii++){
		std::string name = *ii;
		if(name.compare("ball")!=0 && name!=robotName ){
			//pozycja przeszkody w ukladzie z plansza
			//if(Videoserver::data.getSpeed(name).second.x!=0 ||
			//		Videoserver::data.getSpeed(name).second.y!=0){
			Vector2D tmp=Videoserver::data.getPosition(name) * s;;
			file<<"\\put"<<tmp<<"{\\circle*{5}}\n";
			//}

		}
	}
	file<<"\\end{picture}\n"<<std::endl;
	file.close();
}
*/
