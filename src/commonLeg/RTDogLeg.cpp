#include "RTDogLeg.h"

RTDogLeg::RTDogLeg(Servo u, Servo v, RTDogLegTrack* track): _servoU(u), _servoV(v), _track(track) {
	_time = 0;
	_feedByte = 0;
	_currentTrack = 0;
	_trackTime = 0;
	_isActing = false;
}

void RTDogLeg::syncCommandExecutor() {
	feedBack(true);
	return;
}

void RTDogLeg::bumpCommandExecutor(time_type t) {
	_time = t;
	feedBack(true);
	return;
}

void RTDogLeg::trackNewCommandExecutor(byte id, byte type) {
	if(id >= LEG_TRACK_CAPACITY) {
		feedBack(false);
		return;
	}
	_track[id] = RTDogLegTrack();
	feedBack(true);
	return;
}

void RTDogLeg::trackClearCommandExecutor(byte id) {
	if(id >= LEG_TRACK_CAPACITY) {
		feedBack(false);
		return;
	}
	_track[id].clear();
	feedBack(true);
	return;
}

void RTDogLeg::trackAddPointCommandExecutor(byte id, Point p, time_type t) {
	if(id >= LEG_TRACK_CAPACITY) {
		feedBack(false);
		return;
	}
	RTDogLegPos pos(p);
	feedBack(_track[id].addPoint(t, pos));
	return;
}

void RTDogLeg::trackRunCommandExecutor(byte id, time_type t) {
	if(id >= LEG_TRACK_CAPACITY) {
		feedBack(false);
		return;
	}
	_trackTime = t;
	_currentTrack = id;
	_isActing = true;
	feedBack(true);
	return;
}

void RTDogLeg::trackStopCommandExecutor() {
	_isActing = false;
	feedBack(true);
	return;
}

void RTDogLeg::trackMoveCommandExecutor(byte id, Point offset) {
	_track[id].setOffset(offset);
	feedBack(true);
	return;
}

void RTDogLeg::writeCommandExecutor(Point p) {
	_isActing = false;
	RTDogLegPos pos = RTDogLegPos(p);
	ServoPos servo = pos.getServoPos();
	_servoU.write(realUPos(servo.u));
	_servoV.write(realVPos(servo.v));
	feedBack(true);
	return;
}

void RTDogLeg::act() {
	if(!_isActing) return;
	_trackTime += ACT_TIME_STEP;
	RTDogLegPos pos = _track[_currentTrack].getPos(_trackTime);
	ServoPos servo = pos.getServoPos();
	_servoU.write(realUPos(servo.u));
	_servoV.write(realVPos(servo.v));
}

byte RTDogLeg::getFeedBack() {
	return _feedByte;
}

void RTDogLeg::feedBack(bool isOK) {
	if(isOK) _feedByte = RTDogProtocol::CMD_STAT_OK;
	else _feedByte = RTDogProtocol::CMD_STAT_BAD;
}

byte RTDogLeg::realUPos(int u) {
	return 180 - u;
}
byte RTDogLeg::realVPos(int v) {
	return v;
}
