/*
 * Config.h
 *
 *  Created on: 2009-12-02
 *      Author: maciek
 */

#ifndef CONFIG_H_
#define CONFIG_H_


#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <boost/tuple/tuple.hpp>

#include "../additional.h"

class Config {
private:
	class RRTCfg{
	public:
		RRTCfg(){
			goalProb=0.5;
		};
		//prawdopodobienstwo kierowania robota na cel
		double goalProb;
		//promien okregu opisujacego przeszkode/robota
		double robotRadius;
		//odleglosc do jakiej planujemy sciezke za pomoca rrt
		double minDistance;
		//estymowana odleglosc jaka moze przemierzyc robot w trakcie 1 iteracji
		double robotReach;
		Pose goalPose;
	};
	class TestCfg{
	public:
		//czas trwania jednego testu
		time_t testTime;
		//nazwa testowanego modelu
		std::string modelName;
		//zestawy predkosci do kolejnych testow
		std::vector<boost::tuple<double,double,double> > velocities;
		std::vector<Pose > positions;
		//wspo skalujacy predkosci;
		double speedFactor;
	};
public:
	Config();
	bool load(std::string configFileName);
	const std::vector<std::string> getBlueTeam()const;
	const std::vector<std::string> getRedTeam()const;
	std::string getTestModelName();
	time_t getTestEstimatedTime();
	const double getSpeedFactor() const;
	const std::vector<boost::tuple<double,double,double> > getVelTests() const;
	const std::vector<Pose > getPoseTests() const;
	const double getRRTGoalProb() const;
	const double getRRTMinDistance() const;
	const double getRRTRobotReach() const;
	const double getRRTRobotRadius() const;
	const Pose getRRTGoalPose() const;
	bool isTestMode();
	void setTestMode(bool );
	static Config& getInstance(){
		static Config Config_;
		return Config_;
	}
	virtual ~Config();

private:
	//konfiguracja pojedynczego testu
	TestCfg testCfg;
	//konfiguracja algorytmu planowania sciezki
	RRTCfg rrtCfg;
	bool testMode;
	//nazwy modeli druzyny niebieskiej
	std::vector<std::string> blueTeam;
	//nazwy modeli druzyny czerwonej
	std::vector<std::string> redTeam;
	const std::string configFileName;

	bool loadTestMode(xmlNodePtr node,xmlDocPtr config);
	bool loadSettings(xmlNodePtr node,xmlDocPtr config);
	bool loadBlueTeam(xmlNodePtr node,xmlDocPtr config);
	bool loadRedTeam(xmlNodePtr node,xmlDocPtr config);
	bool loadRRTCfg(xmlNodePtr node,xmlDocPtr config);

};

#endif /* CONFIG_H_ */
