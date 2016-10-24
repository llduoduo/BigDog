#include "RTDogLegTrack.h"

RTDogLegTrack::RTDogLegTrack() {
	beginIter = new TimedPoint();
	endIter = new TimedPoint();
	endIter -> next = 0;
	beginIter -> t = 0;
	beginIter -> pos = RTDogLegPos();
	beginIter -> next = endIter;

	_offset = {0, 0};
	_totalTime = 0;
}

RTDogLegTrack::~RTDogLegTrack() {
	while(beginIter -> next) {
		TimedPoint *i = beginIter -> next;
		if(i == endIter) break;
		beginIter -> next = i -> next;
		delete i;
	}
	delete beginIter;
	delete endIter;
}

TimedPoint* RTDogLegTrack::begin() {
	return beginIter;
}

TimedPoint* RTDogLegTrack::end() {
	return endIter;
}

bool RTDogLegTrack::addPoint(time_type t, RTDogLegPos pos) {
	if(t == 0) {
		beginIter -> pos = pos;
		return true;
	}
	if(t > _totalTime) _totalTime = t;
	TimedPoint *p = beginIter;
	TimedPoint *q = p -> next;
	while(q != endIter) {
		if(p -> t == t) return false;
		if(q -> t > t) break;
		p = q;
		q = p -> next;
	}
	TimedPoint *newIter = new TimedPoint();
	newIter -> t = t;
	newIter -> pos = pos;
	newIter -> next = q;
	p -> next = newIter;
	return true;
}

void RTDogLegTrack::setOffset(Point offset) {
	_offset = offset;
}

void RTDogLegTrack::setOffset(double ox, double oy) {
	_offset = {ox, oy};
}

RTDogLegPos RTDogLegTrack::getPos(time_type t) {
	t %= _totalTime;
	TimedPoint *p = beginIter;
	TimedPoint *q = p -> next;
	while(q != endIter) {
		if(p -> t == t) break;
		if(q -> t <= t) {
			p = q;
			q = p -> next;
			continue;
		}
		time_type t0 = p -> t, t1 = q -> t;
		double x0 = p -> pos.getPoint().x, y0 = p -> pos.getPoint().y;
		double x1 = q -> pos.getPoint().x, y1 = q -> pos.getPoint().y;
		double k = double(t - t0) / double(t1 - t0);
		double x = (1.0 - k) * x0 + k * x1;
		double y = (1.0 - k) * y0 + k * y1;
		return RTDogLegPos(x + _offset.x, y + _offset.y);
	}
	return p -> pos;
}

void RTDogLegTrack::clear() {
	while(beginIter -> next) {
		TimedPoint *i = beginIter -> next;
		if(i == endIter) break;
		beginIter -> next = i -> next;
		delete i;
	}
	beginIter = new TimedPoint();
	endIter = new TimedPoint();
	endIter -> next = 0;
	beginIter -> t = 0;
	beginIter -> pos = RTDogLegPos();
	beginIter -> next = endIter;

	_offset = {0, 0};
	_totalTime = 0;
}

void RTDogLegTrack::log() {
	// TimedPoint *i = beginIter;
	// while(i != endIter) {
	// 	RTDogLog::log("t:" + String(i -> t));
	// 	i -> pos.log();
	// 	i = i -> next;
	// }
}
