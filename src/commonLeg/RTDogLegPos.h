#pragma once

#include "RTDogMacros.h"

class RTDogLegBasic
{
public:

	const static Point O;

	const static double R1 = 100;
	const static double L1 = 100;

	const static double x0 = -150.0;
	const static double y0 = -200.0;

	static bool intersection(Point o1,Point o2,double r1,double r2,Point &p1,Point &p2);
};

class RTDogLegPos
{
public:
	RTDogLegPos();
	RTDogLegPos(Point p);
	RTDogLegPos(ServoPos s);
	RTDogLegPos(double x, double y);

	Point getPoint();
	ServoPos getServoPos();

	void log();
private:
	Point _point;
	ServoPos _servo;

	void calcServoPos();
	void calcPoint();
};