#include "RTDogCommand.h"

int RTDogProtocol::syncCommand(byte* command) {
	RTDogSyncCommand cmd;
	cmd.generate(command);
	return cmd.getLength();
}
int RTDogProtocol::bumpCommand(byte* command, time_type t) {
	RTDogBumpCommand cmd(t);
	cmd.generate(command);
	return cmd.getLength();
}
int RTDogProtocol::trackNewCommand(byte* command, byte id, byte type) {
	RTDogTrackNewCommand cmd(id, type);
	cmd.generate(command);
	return cmd.getLength();
}
int RTDogProtocol::trackClearCommand(byte* command, byte id) {
	RTDogTrackClearCommand cmd(id);
	cmd.generate(command);
	return cmd.getLength();
}
int RTDogProtocol::trackAddPointCommand(byte* command, byte id, Point p, time_type t) {
	RTDogTrackAddPointCommand cmd(id, p, t);
	cmd.generate(command);
	return cmd.getLength();
}
int RTDogProtocol::trackRunCommand(byte* command, byte id, time_type t) {
	RTDogTrackRunCommand cmd(id, t);
	cmd.generate(command);
	return cmd.getLength();
}
int RTDogProtocol::trackStopCommand(byte* command) {
	RTDogTrackStopCommand cmd;
	cmd.generate(command);
	return cmd.getLength();
}
int RTDogProtocol::trackMoveCommand(byte* command, byte id, Point offset) {
	RTDogTrackMoveCommand cmd(id, offset);
	cmd.generate(command);
	return cmd.getLength();
}
int RTDogProtocol::writeCommand(byte* command, Point p) {
	RTDogWriteCommand cmd(p);
	cmd.generate(command);
	return cmd.getLength();
}
bool RTDogProtocol::parseCommand(byte* command,int length, RTDogCommandExecutor* e) {
	if(!checkCommand(command, length)) return false;

	switch(command[0]) {
		case CMD_SYNC: {
			RTDogSyncCommand syncCmd;
			if(syncCmd.parse(command, length)) {
				e->syncCommandExecutor();
				return true;
			}
		}
		break;

		case CMD_BUMP: {
			RTDogBumpCommand bumpCmd;
			if(bumpCmd.parse(command, length)) {
				e->bumpCommandExecutor(bumpCmd.getTime());
				return true;
			}
		}
		break;

		case CMD_TRACK_NEW: {
			RTDogTrackNewCommand trackNewCmd;
			if(trackNewCmd.parse(command, length)) {
				e->trackNewCommandExecutor(trackNewCmd.getTrackID(), trackNewCmd.getTrackType());
				return true;
			}
		}
		break;

		case CMD_TRACK_CLEAR: {
			RTDogTrackClearCommand trackClearCmd;
			if(trackClearCmd.parse(command, length)) {
				e->trackClearCommandExecutor(trackClearCmd.getTrackID());
				return true;
			}
		}
		break;

		case CMD_TRACK_ADD: {
			RTDogTrackAddPointCommand trackAddCmd;
			if(trackAddCmd.parse(command, length)) {
				e->trackAddPointCommandExecutor(trackAddCmd.getTrackID(), trackAddCmd.getPoint(), trackAddCmd.getTime());
				return true;
			}
		}
		break;

		case CMD_TRACK_RUN: {
			RTDogTrackRunCommand trackRunCmd;
			if(trackRunCmd.parse(command, length)) {
				e->trackRunCommandExecutor(trackRunCmd.getTrackID(), trackRunCmd.getTime());
				return true;
			}
		}
		break;

		case CMD_TRACK_STOP: {
			RTDogTrackStopCommand trackStopCmd;
			if(trackStopCmd.parse(command, length)) {
				e->trackStopCommandExecutor();
				return true;
			}
		}
		break;

		case CMD_TRACK_MOVE: {
			RTDogTrackMoveCommand trackMoveCmd;
			if(trackMoveCmd.parse(command, length)) {
				e->trackMoveCommandExecutor(trackMoveCmd.getTrackID(), trackMoveCmd.getOffset());
				return true;
			}
		}

		case CMD_WRITE: {
			RTDogWriteCommand writeCmd;
			if(writeCmd.parse(command, length)) {
				e->writeCommandExecutor(writeCmd.getPoint());
				return true;
			}
		}
		break;

		default:
		//RTDogLog::log("invalid command type!");
		break;
	}
	return false;
}
bool RTDogProtocol::checkCommand(byte* command, int length) {
	if(length < 2) {
		//RTDogLog::log("invalid command length!");
		return false;
	}
	byte sum = 0;
	for(int i = 0; i < length - 1; i++) {
		sum ^= command[i];
	}
	if(sum != command[length - 1]) {
		//RTDogLog::log("command check failed!");
		return false;
	}

	return true;
}

RTDogCommand::RTDogCommand(byte typeBit, int length): _typeBit(typeBit), _length(length) {}
int RTDogCommand::getLength() {
	return _length;
}
byte RTDogCommand::checkBit(byte* command) {
	byte sum = 0;
	for(int i = 0; i < _length - 1; i++) sum^= command[i];
	return sum;
}

RTDogSyncCommand::RTDogSyncCommand(): RTDogCommand(RTDogProtocol::CMD_SYNC,2) {}
bool RTDogSyncCommand::parse(byte* command, int length) {
	if(length != _length) {
		//RTDogLog::log("wrong command length!");
		return false;
	}
	return true;
}
void RTDogSyncCommand::generate(byte* command) {
	command[0] = _typeBit;
	command[1] = checkBit(command);
}

RTDogBumpCommand::RTDogBumpCommand(): RTDogCommand(RTDogProtocol::CMD_BUMP,6), _time(0) {}
RTDogBumpCommand::RTDogBumpCommand(time_type t): RTDogCommand(RTDogProtocol::CMD_BUMP,6), _time(t) {}
bool RTDogBumpCommand::parse(byte* command, int length) {
	if(length != _length) {
		//RTDogLog::log("wrong command length!");
		return false;
	}

	DataUnion data;
	for(int i = 0; i < 4; i++)
		data.b[i] = command[i + 1];
	_time = data.timeData;

	return true;
}
void RTDogBumpCommand::generate(byte* command) {
	DataUnion data;
	data.timeData = _time;

	command[0] = _typeBit;
	for(int i = 0; i < 4; i++) 
		command[i+1] = data.b[i];
	command[_length - 1] = checkBit(command);
}
time_type RTDogBumpCommand::getTime() {
	return _time;
}

RTDogTrackNewCommand::RTDogTrackNewCommand(): RTDogCommand(RTDogProtocol::CMD_TRACK_NEW,4), _trackID(0), _trackType(0) {}
RTDogTrackNewCommand::RTDogTrackNewCommand(byte id, byte type): RTDogCommand(RTDogProtocol::CMD_TRACK_NEW,4), _trackID(id), _trackType(type) {}
bool RTDogTrackNewCommand::parse(byte* command, int length) {
	if(length != _length) {
		//RTDogLog::log("wrong command length!");
		return false;
	}

	_trackID = command[1];
	_trackType = command[2];

	return true;
}
void RTDogTrackNewCommand::generate(byte* command) {
	command[0] = _typeBit;
	command[1] = _trackID;
	command[2] = _trackType;
	command[3] = checkBit(command);
}
byte RTDogTrackNewCommand::getTrackID() {
	return _trackID;
}
byte RTDogTrackNewCommand::getTrackType() {
	return _trackType;
}

RTDogTrackClearCommand::RTDogTrackClearCommand(): RTDogCommand(RTDogProtocol::CMD_TRACK_CLEAR,3), _trackID(0) {}
RTDogTrackClearCommand::RTDogTrackClearCommand(byte id): RTDogCommand(RTDogProtocol::CMD_TRACK_CLEAR,3), _trackID(id) {}
bool RTDogTrackClearCommand::parse(byte* command, int length) {
	if(length != _length) {
		//RTDogLog::log("wrong command length!");
		return false;
	}

	_trackID = command[1];

	return true;
}
void RTDogTrackClearCommand::generate(byte* command) {
	command[0] = _typeBit;
	command[1] = _trackID;
	command[2] = checkBit(command);
}
byte RTDogTrackClearCommand::getTrackID() {
	return _trackID;
}

RTDogTrackAddPointCommand::RTDogTrackAddPointCommand(): RTDogCommand(RTDogProtocol::CMD_TRACK_ADD,15), _point({0,0}), _trackID(0), _time(0) {}
RTDogTrackAddPointCommand::RTDogTrackAddPointCommand(byte id, Point p, time_type time): RTDogCommand(RTDogProtocol::CMD_TRACK_ADD,15), _trackID(id), _point(p), _time(time) {}
bool RTDogTrackAddPointCommand::parse(byte* command, int length) {
	if(length != _length) {
		//RTDogLog::log("wrong command length!");
		return false;
	}

	int pos = 1;
	_trackID = command[pos++];
	DataUnion x,y,t;
	for(int i = 0; i < 4; i++) {
		x.b[i] = command[pos++];
	}
	for(int i = 0; i < 4; i++) {
		y.b[i] = command[pos++];
	}
	for(int i = 0; i < 4; i++) {
		t.b[i] = command[pos++];
	}
	_point.x = x.floatData;
	_point.y = y.floatData;
	_time = t.timeData;

	return true;
}
void RTDogTrackAddPointCommand::generate(byte* command) {
	int pos = 0;
	command[pos++] = _typeBit;
	command[pos++] = _trackID;
	DataUnion x,y,t;
	x.floatData = _point.x;
	y.floatData = _point.y;
	t.timeData = _time;
	for(int i = 0; i < 4; i++) command[pos++] = x.b[i];
	for(int i = 0; i < 4; i++) command[pos++] = y.b[i];
	for(int i = 0; i < 4; i++) command[pos++] = t.b[i];
	command[pos] = checkBit(command);
}
byte RTDogTrackAddPointCommand::getTrackID() {
	return _trackID;
}
Point RTDogTrackAddPointCommand::getPoint() {
	return _point;
}
time_type RTDogTrackAddPointCommand::getTime() {
	return _time;
}

RTDogTrackRunCommand::RTDogTrackRunCommand(): RTDogCommand(RTDogProtocol::CMD_TRACK_RUN,7), _trackID(0), _time(0) {}
RTDogTrackRunCommand::RTDogTrackRunCommand(byte id, time_type t): RTDogCommand(RTDogProtocol::CMD_TRACK_RUN,7), _trackID(id), _time(t) {}
bool RTDogTrackRunCommand::parse(byte* command, int length) {
	if(length != _length) {
		//RTDogLog::log("wrong command length!");
		return false;
	}

	_trackID = command[1];
	DataUnion data;
	for(int i = 0; i < 4; i++)
		data.b[i] = command[i + 2];
	_time = data.timeData;

	return true;
}
void RTDogTrackRunCommand::generate(byte* command) {
	DataUnion data;
	data.timeData = _time;

	command[0] = _typeBit;
	command[1] = _trackID;
	for(int i = 0; i < 4; i++) 
		command[i+2] = data.b[i];
	command[_length - 1] = checkBit(command);
}
byte RTDogTrackRunCommand::getTrackID() {
	return _trackID;
}
time_type RTDogTrackRunCommand::getTime() {
	return _time;
}

RTDogTrackStopCommand::RTDogTrackStopCommand(): RTDogCommand(RTDogProtocol::CMD_TRACK_STOP,2) {}
bool RTDogTrackStopCommand::parse(byte* command, int length) {
	if(length != _length) {
		//RTDogLog::log("wrong command length!");
		return false;
	}

	return true;
}
void RTDogTrackStopCommand::generate(byte* command) {
	command[0] = _typeBit;
	command[1] = checkBit(command);
}

RTDogTrackMoveCommand::RTDogTrackMoveCommand(): RTDogCommand(RTDogProtocol::CMD_TRACK_MOVE,11), _trackID(0), _offset({0,0}) {}
RTDogTrackMoveCommand::RTDogTrackMoveCommand(byte id, Point offset): RTDogCommand(RTDogProtocol::CMD_TRACK_MOVE,11), _trackID(id), _offset(offset) {}
bool RTDogTrackMoveCommand::parse(byte* command, int length) {
	if(length != _length) {
		//RTDogLog::log("wrong command length!");
		return false;
	}
	DataUnion x,y;
	int pos = 1;
	_trackID = command[pos++];
	for(int i = 0; i < 4; i++)
		x.b[i] = command[pos++];
	for(int i = 0; i < 4; i++)
		y.b[i] = command[pos++];
	_offset.x = x.floatData;
	_offset.y = y.floatData;
	return true;
}
void RTDogTrackMoveCommand::generate(byte* command) {
	DataUnion x,y;
	x.floatData = _offset.x;
	y.floatData = _offset.y;

	command[0] = _typeBit;
	int pos = 1;
	command[pos++] = _trackID;
	for(int i = 0; i < 4; i++) 
		command[pos++] = x.b[i];
	for(int i = 0; i < 4; i++) 
		command[pos++] = y.b[i];
	command[_length - 1] = checkBit(command);
}
byte RTDogTrackMoveCommand::getTrackID() {
	return _trackID;
}
Point RTDogTrackMoveCommand::getOffset() {
	return _offset;
}

RTDogWriteCommand::RTDogWriteCommand(): RTDogCommand(RTDogProtocol::CMD_WRITE,10), _point({0,0}) {}
RTDogWriteCommand::RTDogWriteCommand(Point p): RTDogCommand(RTDogProtocol::CMD_WRITE,10), _point(p) {}
bool RTDogWriteCommand::parse(byte* command, int length) {
	if(length != _length) {
		//RTDogLog::log("wrong command length!");
		return false;
	}
	DataUnion x,y;
	int pos = 1;
	for(int i = 0; i < 4; i++)
		x.b[i] = command[pos++];
	for(int i = 0; i < 4; i++)
		y.b[i] = command[pos++];
	_point.x = x.floatData;
	_point.y = y.floatData;
	return true;
}
void RTDogWriteCommand::generate(byte* command) {
	DataUnion x,y;
	x.floatData = _point.x;
	y.floatData = _point.y;

	command[0] = _typeBit;
	int pos = 1;
	for(int i = 0; i < 4; i++) 
		command[pos++] = x.b[i];
	for(int i = 0; i < 4; i++) 
		command[pos++] = y.b[i];
	command[_length - 1] = checkBit(command);
}
Point RTDogWriteCommand::getPoint() {
	return _point;
}