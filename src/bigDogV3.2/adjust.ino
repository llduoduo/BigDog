#define ADJUST_DELTA 1.0
#define ADJUST_DELAY_TIME 30 

const double x = 150.0;
double legY[5] = {0.0, 80.0, 80.0, 80.0, 80.0};
double trackY[5] = {};

unsigned char Re_buf[11], counter = 0;
unsigned char sign = 0;

const double balenceRange = 2.0;

void gyroSetup() {
  byte cmd[COMMAND_MAX_LENGTH];
  int l;

  for(int i = 1; i <= 4; i++) 
  {
    l = RTDogProtocol :: writeCommand(cmd, {x, legY[i]});
    sendCommand(i, cmd, l);
  }
}

void gyroMoveLoop() {
  if (sign)
  {
    sign = 0;
    if (Re_buf[0] == 0x55 && Re_buf [1] == 0x53)   //检查帧头
    {
          double pitchAngle = (short(Re_buf [3] << 8 | Re_buf [2])) / 32768.0 * 180;
          double rollingAngle = (short(Re_buf [5] << 8 | Re_buf [4])) / 32768.0 * 180;
          double courseAngle = (short(Re_buf [7] << 8 | Re_buf [6])) / 32768.0 * 180;
          double temperature = (short(Re_buf [9] << 8 | Re_buf [8])) / 340.0 + 36.25;

          if(!pitchStat(pitchAngle) && !rollingStat(rollingAngle))
          {
            return;
          }

          if(pitchStat(pitchAngle) <= 0 && rollingStat(rollingAngle) >= 0 )
          {
            adjustTrack(1, ADJUST_DELTA);
            adjustTrack(4, -ADJUST_DELTA);
          }
          else if(pitchStat(pitchAngle) <= 0 && rollingStat(rollingAngle) <= 0 )
          {
            adjustTrack(2, -ADJUST_DELTA);
            adjustTrack(3, ADJUST_DELTA);
          }
          else if(pitchStat(pitchAngle) >= 0 && rollingStat(rollingAngle) >= 0 )
          {
            adjustTrack(2, ADJUST_DELTA);
            adjustTrack(3, -ADJUST_DELTA);
          }
          else if(pitchStat(pitchAngle) >= 0 && rollingStat(rollingAngle) <= 0 )
          {
            adjustTrack(1, -ADJUST_DELTA);
            adjustTrack(4, ADJUST_DELTA);
          }

          delay(ADJUST_DELAY_TIME);
    }
  }
}

void gyroLoop() {
  if (sign)
  {
    sign = 0;
    if (Re_buf[0] == 0x55 && Re_buf [1] == 0x53)   //检查帧头
    {
          double pitchAngle = (short(Re_buf [3] << 8 | Re_buf [2])) / 32768.0 * 180;
          double rollingAngle = (short(Re_buf [5] << 8 | Re_buf [4])) / 32768.0 * 180;
          double courseAngle = (short(Re_buf [7] << 8 | Re_buf [6])) / 32768.0 * 180;
          double temperature = (short(Re_buf [9] << 8 | Re_buf [8])) / 340.0 + 36.25;

          if(!pitchStat(pitchAngle) && !rollingStat(rollingAngle))
          {
            return;
          }

          if(pitchStat(pitchAngle) <= 0 && rollingStat(rollingAngle) >= 0 )
          {
            adjustLeg(1, ADJUST_DELTA);
            adjustLeg(4, -ADJUST_DELTA);
          }
          else if(pitchStat(pitchAngle) <= 0 && rollingStat(rollingAngle) <= 0 )
          {
            adjustLeg(2, -ADJUST_DELTA);
            adjustLeg(3, ADJUST_DELTA);
          }
          else if(pitchStat(pitchAngle) >= 0 && rollingStat(rollingAngle) >= 0 )
          {
            adjustLeg(2, ADJUST_DELTA);
            adjustLeg(3, -ADJUST_DELTA);
          }
          else if(pitchStat(pitchAngle) >= 0 && rollingStat(rollingAngle) <= 0 )
          {
            adjustLeg(1, -ADJUST_DELTA);
            adjustLeg(4, ADJUST_DELTA);
          }

          delay(ADJUST_DELAY_TIME);
    }
  }
}

void gyroSerialEvent() 
{
  while (Serial.available()) {
    Re_buf[counter] = (unsigned char)Serial.read();
    if (counter == 0 && Re_buf[0] != 0x55) return; //第0号数据不是帧头
    counter++;
    if (counter == 11)          //接收到11个数据
    {
      counter = 0;             //重新赋值，准备下一帧数据的接收
      sign = 1;
    }
  }
}

/**********************************private*****************************/
void adjustTrack(int id, double delta) {
  byte cmd[COMMAND_MAX_LENGTH];
  int l;
  trackY[id] += delta;
  trackY[id] = trackY[id] < -40 ? -40 : trackY[id];
  trackY[id] = trackY[id] > 40 ? 40 : trackY[id];
  l = RTDogProtocol :: trackMoveCommand(cmd, trackID, {0 , trackY[id]});
  sendCommand(id, cmd, l);
}
void adjustLeg(int id, double delta)
{
  byte cmd[COMMAND_MAX_LENGTH];
  int l;
  legY[id] += delta;
  legY[id] = legY[id] < 0 ? 0 : legY[id];
  legY[id] = legY[id] > HEIGHT ? HEIGHT : legY[id];
  l = RTDogProtocol :: writeCommand(cmd, {x , legY[id]});
  sendCommand(id, cmd, l);
}

inline int pitchStat(double pitchAngle) 
{
  if(pitchAngle > 0 && pitchAngle < 180.0 - balenceRange) return 1;
  else if(pitchAngle < 0 && pitchAngle > -180.0 + balenceRange) return -1;
  else return 0;
}

inline int rollingStat(double rollingAngle)
{
  if(rollingAngle > balenceRange) return 1;
  else if(rollingAngle < -balenceRange) return -1;
  else return 0;
}