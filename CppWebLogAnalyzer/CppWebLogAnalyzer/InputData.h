#ifndef __INPUTDATA_H__
#define __INPUTDATA_H__

class InputData {
public:
	char YYYY[5], MM[3], DD[3];
	char TIME_START[7];
	char TIME_END[7];
	int delay;

public:
	InputData();
	~InputData();
};

#endif