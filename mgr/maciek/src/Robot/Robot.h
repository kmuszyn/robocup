#ifndef ROBOT_H_
#define ROBOT_H_

#include <math.h>
#include <string>

#ifdef GAZEBO
	#include <gazebo/gazebo.h>
#endif

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "../SimControl/SimControl.h"
#include "../Vector2d/Vector2D.h"
#include "../additional.h"
#include "../PidRegulator/PidRegulator.h"
/**
 * @author Maciej Gąbka
 *
 * @brief podstawowa klasa reprezentujaca pojedynczego robota mobilnego
 *
 */
class Robot
{
public:
	Robot(const std::string robotName,const std::string posIfaceName);
	virtual ~Robot();
	///ustalenie dlugofalowej pozycji przez stratega poruszanie sie do celu za pomoca
	///algorytmu CVM
	//void goToPosition(Vector2D position);
	///metoda zwracajaca unikalna nazwe robota
	std::string getRobotName() const ;
	std::string getPosIfaceName() const;
	///metoda ustalajaca predkosci liniowa oraz katowa
	void setSpeed(Vector2D v, double w);
	/// zwraca aktualnie zadane predkosci robota first = V  second = w
	std::pair<Vector2D,double> getCurrentVel() const;

private :
	PidRegulator pidRegulator;
	///zadana predkosc liniowa
	Vector2D v;
	///zadana predkosc katowa
	double w;
	///zmienna okreslajaca nazwer robota, jednoznacznie
	///identyfikujaca go na boisku
	std::string robotName;
	///nazwa interfejsu do pobierania pozycji
	std::string posIfaceName;
	///pozycje dlugofalowe ustalane przez stratega
	//Vector2D goTo;
#ifdef GAZEBO
	///interfejs do symulacji
	 gazebo::PositionIface *posIface;
#endif
	 //biezaca pozycja robota
	 Vector2D position;
	 //biezaca rotacja robota
	 double rot;
	 //czas pomiaru
	 double time;


};

#endif /*ROBOT_H_*/
