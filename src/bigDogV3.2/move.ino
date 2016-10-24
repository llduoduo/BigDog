#define T 100.0

const double x1 = 100.0;
const double x2 = 200.0;
const double y1 = 90.0;
const double y2 = 110.0;

void testMove() {
  byte cmd[COMMAND_MAX_LENGTH];
  int l;
  int id;

  id = 1;
  l  = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 12 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 13 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 23 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 24 * T);
  sendCommand(id, cmd, l);

  id = 2;
  l  = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 12 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 13 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 23 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 24 * T);
  sendCommand(id, cmd, l);

  id = 3;
  l  = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 12 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 13 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 23 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 24 * T);
  sendCommand(id, cmd, l);

  id = 4;
  l  = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 12 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 13 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 23 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 24 * T);
  sendCommand(id, cmd, l);


  for (id = 1; id <= 4; id++) {
    l = RTDogProtocol::trackRunCommand(cmd, trackID, 0);
    sendCommand(id, cmd, l);
  }
}

//updated
// void runForward_phase180() {
//   byte cmd[COMMAND_MAX_LENGTH];
//   const int trackID = 0;
//   int l;
//   int id;

//   {
//     id = 1;
//     l  = RTDogProtocol::trackClearCommand(cmd, trackID);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 0 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 12 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 13 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 23 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 24 * T);
//     sendCommand(id, cmd, l);
//   }
//   {
//     id = 2;
//     l  = RTDogProtocol::trackClearCommand(cmd, trackID);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 0 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 1 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 11 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 12 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 24 * T);
//     sendCommand(id, cmd, l);
//   }
//   {
//     id = 3;
//     l  = RTDogProtocol::trackClearCommand(cmd, trackID);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 0 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 1 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 11 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 12 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 24 * T);
//     sendCommand(id, cmd, l);
//   }
//   {
//     id = 4;
//     l  = RTDogProtocol::trackClearCommand(cmd, trackID);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 0 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 12 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 13 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 23 * T);
//     sendCommand(id, cmd, l);
//     l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 24 * T);
//     sendCommand(id, cmd, l);
//   }

//   for (id = 1; id <= 4; id++) {
//     l = RTDogProtocol::trackRunCommand(cmd, trackID, 0);
//     sendCommand(id, cmd, l);
//   }
// }

void runForward_phase180() 
{
  byte cmd[COMMAND_MAX_LENGTH];
  int l;
  int id;

  id = 1;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 1 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 4 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 5 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 40 * T);
  sendCommand(id, cmd, l);

  id = 2;
  double leg2OriginX = (3.0 * x1 + 4.0 * x2) / 7.0;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg2OriginX, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1 , y1}, 20 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 21 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 24 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 25 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg2OriginX, y1}, 40 * T);
  sendCommand(id, cmd, l);

  id = 3;
  double leg3OriginX = (4.0 * x1 + 3.0 * x2) / 7.0;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg3OriginX, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2 , y1}, 20 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 21 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 24 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 25 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg3OriginX, y1}, 40 * T);
  sendCommand(id, cmd, l);

  id = 4;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 1 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 4 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 5 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 40 * T);
  sendCommand(id, cmd, l);

  for (id = 1; id <= 4; id++) {
    l = RTDogProtocol::trackRunCommand(cmd, trackID, 0);
    sendCommand(id, cmd, l);
  }
}

void runBackward_phase180() 
{
  byte cmd[COMMAND_MAX_LENGTH];
  int l;
  int id;

  id = 4;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 1 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 4 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 5 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 40 * T);
  sendCommand(id, cmd, l);

  id = 3;
  double leg2OriginX = (3.0 * x1 + 4.0 * x2) / 7.0;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg2OriginX, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1 , y1}, 20 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 21 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 24 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 25 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg2OriginX, y1}, 40 * T);
  sendCommand(id, cmd, l);

  id = 2;
  double leg3OriginX = (4.0 * x1 + 3.0 * x2) / 7.0;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg3OriginX, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2 , y1}, 20 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 21 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 24 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 25 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg3OriginX, y1}, 40 * T);
  sendCommand(id, cmd, l);

  id = 1;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 1 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 4 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 5 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 40 * T);
  sendCommand(id, cmd, l);

  for (id = 1; id <= 4; id++) {
    l = RTDogProtocol::trackRunCommand(cmd, trackID, 0);
    sendCommand(id, cmd, l);
  }
}

void runForward_phase45() {
  byte cmd[COMMAND_MAX_LENGTH];
  int l;
  int id;

  id = 1;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 1 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 2 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 3 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 24 * T);
  sendCommand(id, cmd, l);

  id = 2;
  double leg2OriginX = (x1 * 1.0 + x2 * 6.0) / 7.0;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg2OriginX, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1 , y1}, 18 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 19 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 20 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 21 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg2OriginX, y1}, 24 * T);
  sendCommand(id, cmd, l);

  id = 3;
  double leg3OriginX = (x1 * 4.0 + x2 * 3.0) / 7.0; 
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg3OriginX, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2 , y1}, 12 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 13 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 14 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 15 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg3OriginX, y1}, 24 * T);
  sendCommand(id, cmd, l);

  id = 4;
  double leg4OriginX = (x1 * 5.0 + x2 * 2.0) / 7.0;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg4OriginX, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 6 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 7 * T );
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 8 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 9 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg4OriginX, y1}, 24 * T);
  sendCommand(id, cmd, l);

  for (id = 1; id <= 4; id++) {
    l = RTDogProtocol::trackRunCommand(cmd, trackID, 0);
    sendCommand(id, cmd, l);
  }

}

void runForward_phase90() {
  byte cmd[COMMAND_MAX_LENGTH];
  int l;
  int id;

  id = 1;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 1 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 5 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 6 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 24 * T);
  sendCommand(id, cmd, l);

  id = 2;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1 , y1}, 18 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 19 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 23 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 24 * T);
  sendCommand(id, cmd, l);

  id = 3;
  double leg3OriginX = (x1 * 2.0 + x2 * 1.0) / 3.0;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg3OriginX, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2 , y1}, 12 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 13 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 17 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 18 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg3OriginX, y1}, 24 * T);
  sendCommand(id, cmd, l);

  id = 4;
  double leg4OriginX = (x1 * 2.0 + x2 * .0) / 3.0;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg4OriginX, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 6 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 7 * T );
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 11 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 12 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg4OriginX, y1}, 24 * T);
  sendCommand(id, cmd, l);

  for (id = 1; id <= 4; id++) 
  {
    l = RTDogProtocol::trackRunCommand(cmd, trackID, 0);
    sendCommand(id, cmd, l);
  }

}

void runBackward() {
  byte cmd[COMMAND_MAX_LENGTH];
  int l;
  int id;

  id = 1;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 1 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 4 *T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 5 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 24 * T);
  sendCommand(id, cmd, l);

  id = 2;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 18 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 19 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 20 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 24 * T);
  sendCommand(id, cmd, l);

  id = 3;
  double leg3OriginX = (x1 * 1.0 + x2 * 2.0) / 3.0;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg3OriginX, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1 , y1}, 12 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 13 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 17 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y1}, 18 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg3OriginX, y1}, 24 * T);
  sendCommand(id, cmd, l);

  id = 4;
  double leg4OriginX = (x1 * 1.0 + x2 * 2.0) / 3.0;
  l = RTDogProtocol::trackClearCommand(cmd, trackID);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg4OriginX, y1}, 0 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2 , y1}, 6 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x2, y2}, 7 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y2}, 11 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {x1, y1}, 12 * T);
  sendCommand(id, cmd, l);
  l = RTDogProtocol::trackAddPointCommand(cmd, trackID, {leg4OriginX, y1}, 24 * T);
  sendCommand(id, cmd, l);

  for (id = 1; id <= 4; id++) 
  {
    l = RTDogProtocol::trackRunCommand(cmd, trackID, 0);
    sendCommand(id, cmd, l);
  }

}
