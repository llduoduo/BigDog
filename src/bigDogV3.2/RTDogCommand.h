#pragma once

#include <Arduino.h>
#include "RTDogMacros.h"

#define COMMAND_MAX_LENGTH 30

typedef union dataUnion {
	byte b[4];
	time_type timeData;
	float floatData;
}DataUnion;

class RTDogCommandExecutor
{
public:
	RTDogCommandExecutor() {}
	virtual ~RTDogCommandExecutor() {}

	virtual void syncCommandExecutor() = 0;
	virtual void bumpCommandExecutor(time_type) = 0;
	virtual void trackNewCommandExecutor(byte id, byte type) = 0;
	virtual void trackClearCommandExecutor(byte id) = 0;
	virtual void trackAddPointCommandExecutor(byte id, Point , time_type) = 0;
	virtual void trackRunCommandExecutor(byte id, time_type) = 0;
	virtual void trackStopCommandExecutor() = 0;
	virtual void trackMoveCommandExecutor(byte id, Point offset) = 0;
	virtual void writeCommandExecutor(Point) = 0;
};

class RTDogProtocol
{
public:
	static const byte CMD_SYNC = 0x00;
	static const byte CMD_STAT_OK = 0x01;
	static const byte CMD_STAT_BAD = 0x02;

	static const byte CMD_BUMP = 0x10;

	static const byte CMD_TRACK_NEW = 0x20;
	static const byte CMD_TRACK_TYPE_1 = 0x21;
	static const byte CMD_TRACK_TYPE_2 = 0x22;

	static const byte CMD_TRACK_CLEAR = 0x30;
	static const byte CMD_TRACK_ADD = 0x31;
	static const byte CMD_TRACK_RUN = 0x32;
	static const byte CMD_TRACK_STOP = 0x33;
	static const byte CMD_TRACK_MOVE = 0x34;

	static const byte CMD_WRITE = 0x40;

	static int syncCommand(byte*);
	static int bumpCommand(byte*, time_type);
	static int trackNewCommand(byte*, byte id, byte type); //
	static int trackClearCommand(byte*, byte id);
	static int trackAddPointCommand(byte*, byte id, Point, time_type);
	static int trackRunCommand(byte*, byte id, time_type);
	static int trackStopCommand(byte*);
	static int trackMoveCommand(byte*, byte id, Point offset);
	static int writeCommand(byte*, Point);

	static bool parseCommand(byte*,int l, RTDogCommandExecutor*);

private:
	static bool checkCommand(byte*, int);
};

class RTDogCommand
{
// TYPE_BIT | PARAMS.. | CHECK_BIT
public:
	RTDogCommand(byte, int);
	virtual ~RTDogCommand() {}

	virtual bool parse(byte*, int) = 0;
	virtual void generate(byte*) = 0;
	int getLength();
protected:
	const byte _typeBit;
	const byte _length;
	byte checkBit(byte*);
};

class RTDogSyncCommand : public RTDogCommand
{
//CMD_SYNC | CHECK_BIT
public:
	RTDogSyncCommand();
	bool parse(byte*, int);
	void generate(byte*);
};

class RTDogBumpCommand : public RTDogCommand
{
//CMD_BUMP | time | CHECK_BIT
public:
	RTDogBumpCommand();
	RTDogBumpCommand(time_type t);
	bool parse(byte*, int);
	void generate(byte*);

	time_type getTime();
private:
	time_type _time;
};

class RTDogTrackNewCommand : public RTDogCommand
{
//CMD_TRACK_NEW | TRACK_ID | TYPE | CHECK_BIT
public:
	RTDogTrackNewCommand();
	RTDogTrackNewCommand(byte id, byte type);
	bool parse(byte*, int);
	void generate(byte*);

	byte getTrackID();
	byte getTrackType();
private:
	byte _trackID;
	byte _trackType;
};

class RTDogTrackClearCommand : public RTDogCommand
{
//CMD_TRACK_CLEAR | TRACK_ID | CHECK_BIT
public:
	RTDogTrackClearCommand();
	RTDogTrackClearCommand(byte id);
	bool parse(byte*, int);
	void generate(byte*);

	byte getTrackID();
private:
	byte _trackID;
};

class RTDogTrackAddPointCommand : public RTDogCommand
{
//CMD_TRACK_ADD | TRACK_ID | p.x | p.y | t | CHECK_BIT
public:
	RTDogTrackAddPointCommand();
	RTDogTrackAddPointCommand(byte id, Point p, time_type t);
	bool parse(byte*, int);
	void generate(byte*);

	byte getTrackID();
	Point getPoint();
	time_type getTime();
private:
	byte _trackID;
	Point _point;
	time_type _time;
};

class RTDogTrackRunCommand : public RTDogCommand
{
//CMD_TRACK_RUN | TRACK_ID | t | CHECK_BIT
public:
	RTDogTrackRunCommand();
	RTDogTrackRunCommand(byte id, time_type);
	bool parse(byte*, int);
	void generate(byte*);

	byte getTrackID();
	time_type getTime();
private:
	byte _trackID;
	time_type _time;
};

class RTDogTrackStopCommand : public RTDogCommand
{
//CMD_TRACK_STOP | CHECK_BIT
public:
	RTDogTrackStopCommand();
	bool parse(byte*, int);
	void generate(byte*);
};

class RTDogTrackMoveCommand : public RTDogCommand
{
//CMD_TRACK_MOVE | TRACK_ID | point.x | point.y | CHECK_BIT
public:
	RTDogTrackMoveCommand();
	RTDogTrackMoveCommand(byte id, Point offset);
	bool parse(byte*, int);
	void generate(byte*);

	byte getTrackID();
	Point getOffset();
private:
	byte _trackID;
	Point _offset;
};

class RTDogWriteCommand : public RTDogCommand
{
//CMD_WRITE | point.x | point.y | CHECK_BIT
public:
	RTDogWriteCommand();
	RTDogWriteCommand(Point p);
	bool parse(byte*, int);
	void generate(byte*);

	Point getPoint();
private:
	Point _point;
};
