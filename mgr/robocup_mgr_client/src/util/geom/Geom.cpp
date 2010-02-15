/*
 * Geom.cpp
 *
 *  Created on: 2010-01-31
 *      Author: kamil
 */

#include "Geom.h"
#include "videoServer/VideoServer.h"
#include "config/AppConfig.h"

Geom::Geom() {
	// TODO Auto-generated constructor stub

}

Geom::~Geom() {
	// TODO Auto-generated destructor stub
}


bool Geom::isPathClear(const Vector2d & start, const Vector2d & end, const list<Vector2d> & obstacles){

	/*
	 * 		 end
	 * 		|\
	 *	a	| \ c
	 *  	|  \
	 *      |   \
	 *      |   / obstacle
	 *      |  /b
	 *      | /
	 *      start
	 *
	 */

	list<Vector2d>::const_iterator i = obstacles.begin();

//	cout<<"Start: "<<start<<" end: "<<end<<endl;

	for(; i!= obstacles.end(); i++){

//		cout<<"Obstacle: "<<*i<<endl;

		Vector2d a, a_,  b, c;
		a = end - start;
		a_ = start - end;
		b = *i - start;
		c = *i - end;

//		cout<<"a: "<<a<<endl;
//		cout<<"a_: "<<a_<<endl;
//		cout<<"b: "<<b<<endl;
//		cout<<"c: "<<c<<endl;
//
//		cout<<"a-b: "<<a.angleTo(b)<<endl;
//		cout<<"a_-c: "<<a_.angleTo(c)<<endl;

		if (fabs(a.angleTo(b)) <= M_PI_2 && fabs(a_.angleTo(c)) <= M_PI_2){
//			cout << "Obstacle may collide\n";
			if (i->distance(start, end) < 2 * AppConfig::instance().radius
					+ AppConfig::instance().safetyMargin) {
//				cout << "Collision!\n";
				return false;
			}
		}


		/*double a = (start - end).length();
		double b = (*i - start).length();
		double c = (*i - end).length();

		cout<<"a,b,c: "<<a<<","<<b<<","<<c<<endl;

		if (a<b+c){	//obstacle is somewhere beetwen start and end
			cout<<"Obstacle may collide\n";
			if (i->distance(start,end) < 2 * AppConfig::instance().radius + AppConfig::instance().safetyMargin){
				cout<<"Collision!\n";
				return false;
			}
		}*/
	}
//	cout<<"path free\n";
	return true;
}

bool Geom::pointCollides(const Vector2d & point, const list<Vector2d> & obstacles){
	list<Vector2d>::const_iterator i = obstacles.begin();

	for (; i != obstacles.end(); i++) {
		if ((*i - point).length() < 2 * AppConfig::instance().radius +
									+ AppConfig::instance().safetyMargin)
			return true;
	}
	return false;

}
