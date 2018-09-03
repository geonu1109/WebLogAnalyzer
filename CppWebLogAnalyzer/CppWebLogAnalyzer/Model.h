#ifndef __MODEL_H__
#define __MODEL_H__

#include "DataConfig.h"
#include "DataInput.h"
#include <cstdio>

class Model
{
public:
	const DataConfig *pConfig;
	char **field;
	char record[2048];

public:
	Model(const DataConfig &config);
	~Model();
	void function1(const DataInput *data);
	void function3(const DataInput *pData);

private:
	void splitBuffer(char *record);
	int isValidTime(const DataInput *pData);
	FILE *getIFP(const DataInput *pData, int iAP);
	FILE *getOFP(const DataInput *pData, int iAP, int iProc);
	int getHour(void);
	int getMinute(void);
	int getSecond(void);
};

#endif