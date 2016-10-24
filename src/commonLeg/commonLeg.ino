#include <Wire.h>
#include <Servo.h>
#include <MsTimer2.h>

#include "Config.h"
#include "RTDogLegPos.h"
#include "RTDogLegTrack.h"
#include "RTDogCommand.h"
#include "RTDogLeg.h"

Servo servoU,servoV;
RTDogLegTrack track[LEG_TRACK_CAPACITY];
RTDogLeg leg(servoU,servoV,track);

byte feedBack;

void legAct() {
  leg.act();
}

void receiveEvent(int l) {
 byte cmd[l];
 byte p = 0;
 while(Wire.available() && p < l) {
   cmd[p++] = Wire.read();
 }
 while(Wire.available());
 if(RTDogProtocol::parseCommand(cmd, l, &leg)) {
   feedBack = leg.getFeedBack();
 } else {
   feedBack = RTDogProtocol::CMD_STAT_BAD;
 }
}
void requestEvent() {
 Wire.write(feedBack);
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin(LEG_ID);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  servoU.attach(SERVO_U);
  servoV.attach(SERVO_V);

  MsTimer2::set(ACT_TIME_STEP, legAct); // 20ms period
  MsTimer2::start();
}

void loop() {
}
