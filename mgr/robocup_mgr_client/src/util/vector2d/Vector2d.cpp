#include "Vector2d.h"
#include <math.h>

Vector2d::Vector2d()
{
	x=0.0;
	y=0.0;
}

Vector2d::Vector2d(double x, double y)
{
	this->x=x;
	this->y=y;
}

Vector2d::~Vector2d()
{
}

Vector2d::Vector2d(const Vector2d & v)
{
	this->x = v.x;
	this->y = v.y;
}

double Vector2d::angleTo(const Vector2d & to) const
{
	double result;


	result=acos( (to.x*this->x +to.y*this->y)/(to.length()*this->length()) );
	double z=this->x*to.y-this->y*to.x;


	if(z>=0)
	return result;
	else return -result;
}

int Vector2d::signOfangleTo(const Vector2d & to) const
{
	double z=this->x*to.y-this->y*to.x;
	if(z>=0)
	return 1;
	else return -1;
}
double Vector2d::scalarProduct(const Vector2d &to)const
{
	double result;

	result=acos( (to.x*this->x +to.y*this->y)/(to.length()*this->length()) );

	return result;
}

Vector2d Vector2d::projectionOn(double a,double b,double c) const
{
	BOOST_ASSERT(a!=0 || b!=0);
	Vector2d result;
	//prosta typu x=const
	if(b==0 && a!=0){
		result=Vector2d(-c/a,this->y);
	}
	//prosta typu y=const
	else if(a==0 && b!=0){
		result=Vector2d(this->x,-c/b);
	}
	//prosta typu y=ax+b
	else{
		double a2=b/a;
		double b2=this->y-a2*this->x;
		double x=(b2-(-c/b))/((-a/b)-a2);
		double y=a2*x +b2;
		result=Vector2d(x,y);
	}
	return result;

}

double Vector2d::length() const
{
	return sqrt( x*x+y*y);
}

double Vector2d::distance(Vector2d to)const
{
	return sqrt(pow(to.x-this->x,2)+pow(to.y-this->y,2));
}

double Vector2d::distance(const Vector2d & start, const Vector2d & end) const{
	//convert line from start-end to Ax+By+C
	double A,B,C;
	if(end.x - start.x == 0){
		A = 1;
		B = 0;
		C = start.y;
	}
	else{
		A = (end.y - start.y) / (end.x - start.x);
		B = -1.0;
		C = start.y - ((end.y-start.y) * start.x / (end.x - start.x));
	}

	double result = fabs((A * this->x) + (B*this->y) + C)/sqrt((A*A) + (B*B));
	return result;
}

Vector2d Vector2d::rotate(double angle){
	double d = this->length();
	double curr_angle = atan2(y,x);
	angle += curr_angle;

	Vector2d res(d * cos(angle), d * sin(angle) );
	return res;
}

Vector2d & Vector2d::operator =(const Vector2d & v)
{
	this->x = v.x;
	this->y = v.y;

	return *this;
}



Vector2d  Vector2d::operator-(const Vector2d & v) const
{
	return Vector2d(x-v.x,y-v.y);
}

Vector2d  Vector2d::operator-(const Vector2d & v)
{
	return Vector2d(x-v.x,y-v.y);
}

bool Vector2d::operator <(const Vector2d & v)
{
	if(this->x <v.x && this->y<v.y)
	{
	return true;
	}
	else
		return false;
}

Vector2d Vector2d::operator +(const Vector2d & v) const
{
	return Vector2d(x+v.x,y+v.y);
}

Vector2d Vector2d::operator*(double d)const
{
	return Vector2d(x*d,y*d);
}


std::ostream & operator<<(std::ostream & os, const Vector2d & v )
{
	os<<"("<<v.x<<","<<v.y<<")";
	return os;
}


