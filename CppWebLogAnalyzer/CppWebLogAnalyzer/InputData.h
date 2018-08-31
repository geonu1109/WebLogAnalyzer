#ifndef __INPUTDATA_H__
#define __INPUTDATA_H__

class InputData {
public:
	char DATE[9];
	char TIME_START[7];
	char TIME_END[7];
	int delay;

public:
	InputData();
	~InputData();
};

#endif