#pragma once

#ifdef WIN32

#include <iostream>
using namespace std;
#define String string

#else

#include <Arduino.h>

#endif

#include <String.h>

#define WIDTH 250.0
#define HEIGHT 150.0

typedef unsigned long time_type;

typedef struct point {
	float x;
	float y;
}Point;

typedef struct servoPos {
	int u;
	int v;
}ServoPos;

class RTDogLog
{
public:
	static void log(String s) {
		#ifdef WIN32
		std::cout<<"RTlog: " + s<<std::endl;
		#else
		Serial.println("RTlog:" + s);
		#endif
	}
};

