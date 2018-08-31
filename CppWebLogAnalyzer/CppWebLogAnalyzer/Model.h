#ifndef __MODEL_H__
#define __MODEL_H__

#include "Config.h"
#include "InputData.h"

class Model
{
public:
	const Config *pConfig;
	char **field;
	char record[2048];

public:
	Model(const Config &config);
	~Model();
	void function1(const InputData *data);
	void splitRecord(char *record);
};

#endif