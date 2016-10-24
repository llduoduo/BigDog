#pragma once

#include <Servo.h>

#include "RTDogMacros.h"
#include "RTDogLegPos.h"
#include "RTDogLegTrack.h"
#include "RTDogCommand.h"

#define LEG_TRACK_CAPACITY 3
#define ACT_TIME_STEP 20

class RTDogLeg : public RTDogCommandExecutor
{
public:
	RTDogLeg(Servo u, Servo v, RTDogLegTrack* track);

	void syncCommandExecutor();
	void bumpCommandExecutor(time_type t);
	void trackNewCommandExecutor(byte id, byte type);
	void trackClearCommandExecutor(byte id);
	void trackAddPointCommandExecutor(byte id, Point p, time_type t);
	void trackRunCommandExecutor(byte id, time_type t);
	void trackStopCommandExecutor();
	void trackMoveCommandExecutor(byte id, Point offset);
	void writeCommandExecutor(Point);

	void act();

	byte getFeedBack();

private:
	time_type _time;
	RTDogLegTrack *_track;

	byte _currentTrack;
	time_type _trackTime;
	bool _isActing;

	void feedBack(bool);
	byte _feedByte;

	Servo _servoU, _servoV;
	byte realUPos(int u);
	byte realVPos(int v);
};