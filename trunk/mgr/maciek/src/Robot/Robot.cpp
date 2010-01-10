#include "Robot.h"

Robot::Robot(const std::string robotName,const std::string posIfaceName)
{
	this->robotName=robotName;
	this->posIfaceName=posIfaceName;
	this->v=Vector2D(0,0);
	this->w=0;
	this->time=0;

	//alokowanie interfejsu do zmiany pozycji
#ifdef GAZEBO
	posIface = new gazebo::PositionIface();
	/// Connect to the libgazebo server
	std::string positionIfaceName=this->robotName+this->posIfaceName;
	SimControl::getInstance().connectGazeboPosIface(posIface,positionIfaceName.c_str());
	//Enable the motor
	posIface->Lock(1);
	posIface->data->cmdEnableMotors = 1;
	posIface->Unlock();
#endif

//	boost::tuple<double,double,double> positions;
//	SimControl::getInstance().getModelPos(robotName,positions);
//	this->position=Vector2D(positions.get<0>(),positions.get<1>());
//	this->rot=positions.get<2>();

}
std::string Robot::getRobotName() const
{
	return this->robotName;
}
std::string Robot::getPosIfaceName() const
{
	return this->posIfaceName;
}
void Robot::setSpeed(Vector2D v, double w)
{
	boost::tuple<double,double,double> currPositions;
	boost::tuple<double,double,double> newVel=boost::tuple<double,double,double> (v.x,v.y,w);
	//SimControl::getInstance().getModelPos(robotName,currPositions);
	/*
	if(this->time!=0){
		double currTime=SimControl::getInstance().getSimTime();
		double deltaTime=currTime-this->time;
		this->pidRegulator.setCmdVel(v,w);
		this->pidRegulator.calculateError( Vector2D( (currPositions.get<0>()-this->position.x)/deltaTime,
				(currPositions.get<1>()-this->position.y)/deltaTime ),
						(currPositions.get<2>()-this->rot)/deltaTime );

		newVel=this->pidRegulator.calculateNewVel();
		this->time=currTime;
	}
	else
		this->time=SimControl::getInstance().getSimTime();
*/
#ifdef GAZEBO
	posIface->Lock(1);
	posIface->data->cmdEnableMotors = 1;
	//posIface->data->cmdVelocity.pos.x = newVel.get<0>();
	posIface->data->cmdVelocity.pos.x = newVel.get<0>();
	posIface->data->cmdVelocity.pos.y = newVel.get<1>();
	posIface->data->cmdVelocity.yaw = newVel.get<2>();
	//posIface->data->cmdVelocity.yaw = 0;
	posIface->Unlock();
#endif
}
std::pair<Vector2D,double> Robot::getCurrentVel() const
{
	return std::pair<Vector2D,double>(this->v,this->w);
}
Robot::~Robot()
{
	std::cout<<"~Robot"<<std::endl;
}
