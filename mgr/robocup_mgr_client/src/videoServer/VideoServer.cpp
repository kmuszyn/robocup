/*
 * VideoServer.cpp
 *
 *  Created on: 2009-12-13
 *      Author: kamil
 */

#include "VideoServer.h"

log4cxx::LoggerPtr VideoServer::logger(log4cxx::Logger::getLogger("videoServer.VideoServer"));

VideoServer & VideoServer::instance(){
	static VideoServer instance;
	return instance;
}

VideoData & VideoServer::data(){
	return videoData;
}

void VideoServer::update(){
	double t1 = SimControl::instance().getSimTime();
	SimControl::instance().update(videoData);
	double t2 = SimControl::instance().getSimTime();
	dTime = t2 - t1;


#ifdef MGR_VIEWER
	updateCounter++;
	writeViewerData();
#endif
}
void VideoServer::display(){
	std::cout<<"VideoData display!\n";
	for (VideoData::iterator i = videoData.begin(); i!= videoData.end(); i++){
		std::cout<<i->first<<" "<<*(i->second)<<std::endl;
	}

	std::cout<<"Time: "<<SimControl::instance().getSimTime()<<std::endl;
}


VideoServer::VideoServer()
#ifdef MGR_VIEWER
	: viewerFile("videoServer.txt")
#endif
{
	LOG4CXX_DEBUG(logger, "VideoServer construct");

	AppConfig & config = AppConfig::instance();

	//filling the data map

	for(std::vector<std::string>::iterator i = config.team1.begin();
		i!= config.team1.end(); i++){
		videoData.insert(std::pair<std::string, Position2d *>((*i), new Position2d()));
	}

	for(std::vector<std::string>::iterator i = config.team2.begin();
		i!= config.team2.end(); i++){
		videoData.insert(std::pair<std::string, Position2d *>((*i), new Position2d()));
	}

	videoData.insert(std::pair<std::string, Position2d *>(config.ball, new Position2d()));

#ifdef MGR_VIEWER
	updateCounter=0;
	std::ofstream file;
	file.open(viewerFile.c_str(),std::ios::out);
	file.close();
#endif
}

double VideoServer::getDTime(){
	return dTime;
}

#ifdef MGR_VIEWER
void VideoServer::writeViewerData(){
	std::ofstream file;
	file.open(viewerFile.c_str(),std::ios::app);
	file.precision(3);
	file<<":step "<<updateCounter<<std::endl;

	//write video data:
	//posx posy rot radius KIND(for ball: rot 0 radius 0.02)
	//kind: 0 - ball, 1 -  member of team 1, 2 - member of team 2
	for (VideoData::iterator i = videoData.begin(); i!= videoData.end(); i++)	{
		if ((*i).first != AppConfig::instance().ball){	//its a robot
			file<<(*i).second->pos.x<<" "<<(*i).second->pos.y<<" "<<(*i).second->rot.degreeValue()
			<<" "<<AppConfig::instance().radius;

			//which team member is it?
			if (std::find(AppConfig::instance().team1.begin(),
					AppConfig::instance().team1.end(), (*i).first) == AppConfig::instance().team1.end() )
				file<<" 2";
			else
				file<<" 1";

			file<<std::endl;
		}
		else
			file<<(*i).second->pos.x<<" "<<(*i).second->pos.y<<" "<<0<<" "<<"0.02 0"<<std::endl;
	}

	file.close();
}
#endif	//mgr_viewer

VideoServer::~VideoServer() {
	// TODO Auto-generated destructor stub
}


