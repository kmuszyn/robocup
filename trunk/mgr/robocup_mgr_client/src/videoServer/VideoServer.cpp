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
	SimControl::instance().update(videoData);
}
void VideoServer::display(){
	std::cout<<"VideoData display!\n";
	for (VideoData::iterator i = videoData.begin(); i!= videoData.end(); i++){
		std::cout<<i->first<<" "<<*(i->second)<<std::endl;
	}
}


VideoServer::VideoServer() {
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

}

VideoServer::~VideoServer() {
	// TODO Auto-generated destructor stub
}
