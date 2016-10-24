#include <Wire.h>

#include "RTDogCommand.h"

// #define DEBUG

#define MOVE
// #define ADJUST

const Point initPoint = {50, 100};
const int trackID = 0;

void sendCommand(int add, byte* command, int l) {
  Wire.beginTransmission(add); // transmit to device #2
  Wire.write(command, l);
  Wire.endTransmission();    // stop transmitting
}

void setup() {
  Serial.begin(115200);

  Wire.begin();

  delay(1000);
  initDog();

  #ifdef MOVE
    runForward_phase180();
  #endif

  #ifdef ADJUST
    gyroSetup();
  #endif
}

void loop() {
  #ifdef ADJUST
    gyroLoop();
  #endif
  #ifdef MOVE
    gyroMoveLoop();
  #endif
}

void serialEvent() {
  //#ifdef ADJUST
    gyroSerialEvent();
  //#endif
}

void initDog() {
  byte cmd[COMMAND_MAX_LENGTH];
  int l = RTDogProtocol::writeCommand(cmd, initPoint);
  for (int id = 1; id <= 4; id++) {
    sendCommand(id, cmd, l);
  }
}
