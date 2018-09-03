#ifndef __MODEL_H__
#define __MODEL_H__

#include "DataConfig.h"
#include "DataInput.h"

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

private:
	void splitBuffer(char *record);
	int isValidTime(const DataInput *pData);
};

#endif