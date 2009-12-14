/*
 * types.h
 *
 *  Created on: 2009-05-04
 *      Author: kamil
 */

#ifndef TYPES_H_
#define TYPES_H_
#include <map>
#include <string>
#include "util/position2d/Position2d.h"

enum TeamName{TEAM1, TEAM2};

typedef std::map<std::string, Position2d * > VideoData;

#endif /* TYPES_H_ */
