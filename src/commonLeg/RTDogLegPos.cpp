#include "RTDogLegPos.h"
#include <math.h>

inline double distance(double x1,double y1,double x2,double y2) {
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

const Point RTDogLegBasic::O = {0, 0};

bool RTDogLegBasic::intersection(Point o1,Point o2,double r1,double r2,Point &p1,Point &p2) {
	double d = distance(o1.x,o1.y,o2.x,o2.y);
	if(d == 0) return false;
	if(d > (r1+r2)) return false;
	if(d < r1 - r2 || d < r2 - r1) return false;
	
	double a = (r1*r1-r2*r2+d*d) / 2.0 / d;
	double h = sqrt(r1*r1 - a*a);
	double tx = o1.x + a * (o2.x - o1.x) / d;
	double ty = o1.y + a * (o2.y - o1.y) / d;
	p1.x = tx + h * (o2.y - o1.y) / d;
	p1.y = ty - h * (o2.x - o1.x) / d;
	p2.x = tx - h * (o2.y - o1.y) / d;
	p2.y = ty + h * (o2.x - o1.x) / d;
	return true;
} 

RTDogLegPos::RTDogLegPos() {
	_point.x = 0;
	_point.y = 0;
	_servo.u = 90;
	_servo.v = 90;
	calcPoint();
}

RTDogLegPos::RTDogLegPos(Point p) {
	_point.x = p.x;
	_point.y = p.y;
	_servo.u = 90;
	_servo.v = 90;
	calcServoPos();
}

RTDogLegPos::RTDogLegPos(double x, double y) {
	_point.x = x;
	_point.y = y;
	_servo.u = 90;
	_servo.v = 90;
	calcServoPos();
}

RTDogLegPos::RTDogLegPos(ServoPos s) {
	_servo.u = s.u;
	_servo.v = s.v;
	_point.x = 0;
	_point.y = 0;
	calcPoint();
}

Point RTDogLegPos::getPoint() {
	return _point;
}

ServoPos RTDogLegPos::getServoPos() {
	return _servo;
}

void RTDogLegPos::calcServoPos() {
	_point.x = _point.x < 0 ? 0 : _point.x;
	_point.x = _point.x > WIDTH ? WIDTH : _point.x;
	_point.y = _point.y < 0 ? 0 : _point.y;
	_point.y = _point.y > HEIGHT ? HEIGHT : _point.y;
	
	Point foot,i1,i2;
	foot.x = _point.x + RTDogLegBasic::x0;
	foot.y = _point.y + RTDogLegBasic::y0;

	if(!RTDogLegBasic::intersection(RTDogLegBasic::O,foot,RTDogLegBasic::L1,RTDogLegBasic::L1,i1,i2)) {
		RTDogLog::log("fail to calc servo pos");
		return;
	}

	double v = atan2(i1.y,i1.x);
	double u = atan2(i2.y,i2.x);
	_servo.u = - u * 180.0 / M_PI + 45.0;
	_servo.v = - v * 180.0 / M_PI - 90.0;

	if(_servo.u > 180) _servo.u -= 360.0;
	if(_servo.v < -180) _servo.v += 360.0;

	// int x0 = floor(_point.x / WIDTH_STEP);
	// int y0 = floor(_point.y / HEIGHT_STEP);
	// double dx = _point.x - (double)x0 * WIDTH_STEP;
	// double dy = _point.y - (double)y0 * HEIGHT_STEP;
	// double k0 = (WIDTH_STEP - dx) * (HEIGHT_STEP - dy) / (WIDTH_STEP * HEIGHT_STEP);
	// double k1 = (WIDTH_STEP - dx) * dy / (WIDTH_STEP * HEIGHT_STEP);
	// double k2 = dx * (HEIGHT_STEP - dy) / (WIDTH_STEP * HEIGHT_STEP);
	// double k3 = dx * dy / (WIDTH_STEP * HEIGHT_STEP);
	// double u = k0 * (double)RTDogLegBasic::servoU[x0][y0] + k1 * (double)RTDogLegBasic::servoU[x0][y0+1] + k2 * (double)RTDogLegBasic::servoU[x0+1][y0] + k3 * (double)RTDogLegBasic::servoU[x0+1][y0+1];
	// double v = k0 * (double)RTDogLegBasic::servoV[x0][y0] + k1 * (double)RTDogLegBasic::servoV[x0][y0+1] + k2 * (double)RTDogLegBasic::servoV[x0+1][y0] + k3 * (double)RTDogLegBasic::servoV[x0+1][y0+1];
	// _servo.u = floor(u + 0.5);
	// _servo.v = floor(v + 0.5);



}

void RTDogLegPos::calcPoint() {
	Point A,B,C;
	
	double su = (-_servo.u + 45.0) / 180.0 * M_PI;
	double sv = (-_servo.v - 90) / 180.0 * M_PI;

	A.x = RTDogLegBasic::O.x + RTDogLegBasic::R1 * cos(su);
	A.y = RTDogLegBasic::O.y + RTDogLegBasic::R1 * sin(su);
	B.x = RTDogLegBasic::O.x + RTDogLegBasic::R1 * cos(sv);
	B.y = RTDogLegBasic::O.y + RTDogLegBasic::R1 * sin(sv);
	
	Point c1,c2;
	if(!RTDogLegBasic::intersection(A,B,RTDogLegBasic::L1,RTDogLegBasic::L1,c1,c2)) {
		RTDogLog::log("fail to calc point pos");
		return;
	}
	C = c2;
	
	_point.x = c2.x;
	_point.y = c2.y;
	_point.x -= RTDogLegBasic::x0;
	_point.y -= RTDogLegBasic::y0;

}

void RTDogLegPos::log() {
	char ts[50];
	sprintf(ts,"pos:[x:%d,y:%d]\tservo:[U:%d,V:%d]", (int)_point.x, (int)_point.y, _servo.u, _servo.v);
	String s(ts);
	RTDogLog::log(s);
}
