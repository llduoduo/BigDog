#pragma once

#include "RTDogMacros.h"
#include "RTDogLegPos.h"

typedef struct timedPoint {
	time_type t;
	RTDogLegPos pos;
	struct timedPoint *next;
}TimedPoint;

class RTDogLegTrack 
{
public:
	RTDogLegTrack();
	~RTDogLegTrack();

	TimedPoint* begin();
	TimedPoint* end();

	bool addPoint(time_type, RTDogLegPos);

	void setOffset(Point);
	void setOffset(double, double);

	RTDogLegPos getPos(time_type t);

	void clear();

	void log();

private:
	TimedPoint *beginIter;
	TimedPoint *endIter;

	Point _offset;

	time_type _totalTime;
};
