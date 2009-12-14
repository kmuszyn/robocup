/*
 * VideoServer.h
 *
 *  Created on: 2009-12-13
 *      Author: kamil
 */

#ifndef VIDEOSERVER_H_
#define VIDEOSERVER_H_

#include "log4cxx/logger.h"
#include <map>
#include <string>
#include "util/position2d/Position2d.h"
#include "config/AppConfig.h"
#include "simControl/SimControl.h"
#include "util/types.h"


/**
 * This class is responsible of modelling video server functions (generating info about robot's positions).
 *
 */
class VideoServer {

public:
	///Main singleton access method
	static VideoServer & instance();

	///Main purpose of videoServer - this method updates videoData. It should be called in evry simulation cycle.
	void update();

	///Returns video server data filled by update method
	const VideoData & data();

	///Displays the content of videoData
	void display();

	~VideoServer();
private:
	VideoServer();
	VideoServer(const VideoServer &);
	VideoServer & operator = (const VideoServer &);

private:
	VideoData videoData;

	///For logging
	static log4cxx::LoggerPtr logger;
};

#endif /* VIDEOSERVER_H_ */
