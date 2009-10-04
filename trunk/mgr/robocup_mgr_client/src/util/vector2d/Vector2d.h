#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <iostream>
#include <boost/assert.hpp>

/* klasa pomocnicza do przechowywania pary liczb 
 * opisujacych pozycje na plaszczyznie 2d
 */

class Vector2d
{
public:
	double x,y;	//publiczne dla prostszego dostepu
	Vector2d();
	Vector2d(double x, double y);
	Vector2d(const Vector2d & );
	~Vector2d();
	
	double length() const;
	//zwraca kat pomiedzy wektorami
	double angleTo(const Vector2d &) const;
	int signOfangleTo(const Vector2d & to) const;
	//iloczyn skalarny
	double scalarProduct(const Vector2d &)const;

	//rzutuje wybrany punkt na prosta Ax+By+C=0
	Vector2d projectionOn(double a, double b,double c) const;
	double distance(Vector2d to) const;
	Vector2d & operator=(const Vector2d &);
	Vector2d  operator-(const Vector2d &)const;
	Vector2d operator-(const Vector2d &);
	Vector2d operator+(const Vector2d &) const;
	///Metoda pozwalająca na przeskalowanie wektora (mnożenie przez skalar).
	Vector2d operator*(double ) const;
	
	bool operator <(const Vector2d & v);
	
	///Zwracająca wektor bazowy obrócony o kąt angle (w radianach).
	Vector2d rotate(double angle);
	
	friend std::ostream & operator<<(std::ostream & os, const Vector2d & v );
};

#endif /*VECTOR2D_H_*/
